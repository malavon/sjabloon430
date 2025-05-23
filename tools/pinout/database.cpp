#include "database.hpp"

#include <cassert>
#include <iostream>
#include <set>

namespace sjabloon430 { namespace tools { namespace pinout { namespace db {

sqlite3 *createDatabase() {
	sqlite3 *db;
	// in-memory is preferred, but exporting should be simple, formatted and not DIY
	// if not, use a file database?
	// unsigned int rc = sqlite3_open("file:debug.db", &db);
	unsigned int rc = sqlite3_open("file::memory:", &db);

	if ( rc != 0 ) {
		sqlite3_close(db);
		db = nullptr;
	} else {
		// this is apparently required for sqlite3 to behave like an actual database ...
		sqlite3_exec(db, "PRAGMA foreign_keys = ON", nullptr, nullptr, nullptr);
	}
	return db;
}

/* Query DB */

void prepare(sqlite3 *db, sqlite3_stmt **stmt, const char *QUERY) {
	int rc = sqlite3_prepare_v2(db, QUERY, -1, stmt, NULL);
	if ( rc != SQLITE_OK ) {
		std::cerr << "SQLite3 error " << sqlite3_errmsg(db) << std::endl;
	}
	assert(rc == SQLITE_OK);
}

DatabaseTotals countTotals(sqlite3 *db) {
	// a single result row is best, 1 column per count
	// this is the best I can do with my knowledge of sqlite
	static const char *QUERY = "SELECT SUM(ds), SUM(dv), SUM(odbl) "
				   "FROM ("
				   "	SELECT 0 AS ds, 0 AS dv, 0 AS odbl "
				   "	UNION SELECT COUNT( * ), 0, 0 FROM datasheet "
				   "	UNION SELECT 0, COUNT( * ), 0 FROM device "
				   "	UNION SELECT 0, 0, COUNT( * ) FROM orderable )";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	DatabaseTotals totals{-1, -1, -1};
	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		totals.datasheets = sqlite3_column_int(stmt, 0);
		totals.devices = sqlite3_column_int(stmt, 1);
		totals.orderables = sqlite3_column_int(stmt, 2);
	}

	return totals;
}

DatabaseTotals countSupported(sqlite3 *db) {
	// a single result row is best, 1 column per count
	// this is the best I can do with my knowledge of sqlite
	static const char *QUERY = "SELECT SUM(ds), SUM(dv), SUM(odbl) FROM ("
				   "	SELECT 0 AS ds, 0 AS dv, 0 AS odbl "
				   "UNION "
				   "	SELECT count(DISTINCT ds.id), 0, 0 "
				   "	FROM datasheet ds "
				   "	INNER JOIN device d ON ds.id = d.datasheet_id "
				   "	INNER JOIN orderable o ON d.model = o.device_id "
				   "	WHERE o.pinset_id NOT NULL "
				   "UNION"
				   "	SELECT 0, COUNT(DISTINCT d.model), 0 "
				   "	FROM device d "
				   "	INNER JOIN orderable o ON d.model = o.device_id "
				   "	WHERE o.pinset_id NOT NULL "
				   "UNION"
				   "	SELECT 0, 0, COUNT(DISTINCT o.name) "
				   "	FROM orderable o "
				   "	WHERE o.pinset_id NOT NULL )";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	DatabaseTotals totals{-1, -1, -1};
	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		totals.datasheets = sqlite3_column_int(stmt, 0);
		totals.devices = sqlite3_column_int(stmt, 1);
		totals.orderables = sqlite3_column_int(stmt, 2);
	}

	return totals;
}

Datasheet findDatasheet(sqlite3 *db, const string id) {
	static const char *QUERY = "SELECT id, revision,"
				   "CONCAT(issue_month, '/', issue_year)	issue_date,"
				   "CONCAT(rev_month, '/', rev_year)	rev_date "
				   "FROM datasheet "
				   "WHERE id=?";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);

	// assume only a single row
	Datasheet ds;
	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		ds.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
		ds.rev = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
		ds.issueDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
		ds.revDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
	}
	return ds;
}

vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId) {
	static const char *QUERY = "SELECT model FROM device "
				   "WHERE datasheet_id = ? "
				   "ORDER BY model ASC";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);

	vector<string> result;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		result.push_back(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0))));
	}
	return result;
}

vector<Orderable> findOrderablesByDatasheet(sqlite3 *db, const string datasheetId) {
	static const char *QUERY = "SELECT name, drawing, pins, pinset_id "
				   "FROM orderable o "
				   "INNER JOIN device d ON o.device_id = d.model "
				   "WHERE datasheet_id = ? "
				   "order by name ASC";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	int rc = sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	assert(SQLITE_OK == rc);

	vector<Orderable> result;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
		string drw = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
		int pins = sqlite3_column_int(stmt, 2);
		int pinsetId = sqlite3_column_int(stmt, 3);
		result.push_back(Orderable{
		    .name = name, .pkg = Package{drw, pins},
			     .pinsetId = pinsetId
		 });
	}
	return result;
}

vector<Signalset> findSignalsetsByDatasheet(sqlite3 *db, const string datasheetId) {
	// this function assumes index is continuous from 0 to n

	static const char *SSET_QUERY =
	    "SELECT DISTINCT datasheet_idx, ss.id signalset_id, ss.parent_id, drawing, pins, pin_bga_row, pin_number "
	    "FROM signalset ss "
	    "INNER JOIN pinset_signalset psss ON ss.id = psss.signalset_id "
	    "INNER JOIN orderable o ON o.pinset_id = psss.pinset_id "
	    "INNER JOIN device d ON o.device_id = d.model "
	    "WHERE d.datasheet_id = ? "
	    "ORDER BY datasheet_idx ASC, ss.parent_id ASC, ss.id ASC";

	static const char *SGNS_QUERY = "SELECT idx, signal_id "
					"FROM signalset_signal sss "
					"INNER JOIN signal s ON s.id = sss.signal_id "
					"WHERE signalset_id = ? "
					"ORDER BY sss.signalset_id ASC, idx ASC";
	static sqlite3_stmt *stmtSset, *stmtSgns;
	if ( stmtSset == nullptr ) {
		prepare(db, &stmtSset, SSET_QUERY);
		prepare(db, &stmtSgns, SGNS_QUERY);
	}

	sqlite3_reset(stmtSset);
	int rc = sqlite3_bind_text(stmtSset, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	assert(SQLITE_OK == rc);

	vector<Signalset> result;
	Signalset s;
	int lastId = 0, id = 0;
	int vrIdx = -1;
	while ( sqlite3_step(stmtSset) == SQLITE_ROW ) {
		// datasheet_idx = sqlite3_column_int(stmt, 0);
		id = sqlite3_column_int(stmtSset, 1);
		if ( lastId != id ) {
			lastId = id;
			s = Signalset();
			s.id = id;
			s.parentId = sqlite3_column_int(stmtSset, 2);
			result.push_back(s);
			vrIdx++;
		}
		string drw = reinterpret_cast<const char *>(sqlite3_column_text(stmtSset, 3));
		int pins = sqlite3_column_int(stmtSset, 4);
		const unsigned char *dbBga = sqlite3_column_text(stmtSset, 5);
		string bgaRow = (dbBga == nullptr) ? "" : reinterpret_cast<const char *>(dbBga);
		int pinNumber = sqlite3_column_int(stmtSset, 6);
		s.pins[Package{drw, pins}] = Pin{bgaRow, pinNumber};
		result[vrIdx] = s; // isn't necessary? no copy-semantics?
	}

	for ( Signalset &s : result ) {
		sqlite3_reset(stmtSgns);
		rc = sqlite3_bind_int(stmtSgns, 1, s.id);
		assert(SQLITE_OK == rc);
		// assumes idx is continuous and starts at 0 -> incorrect once parents are used ...
		while ( sqlite3_step(stmtSgns) == SQLITE_ROW ) {
			// idx = sqlite3_column_int(stmtSgns, 0)
			string sgn = reinterpret_cast<const char *>(sqlite3_column_text(stmtSgns, 1));
			s.signals.push_back(sgn);
		}
	}

	return result;
}

vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId) {
	static const char *QUERY = "SELECT o.drawing, o.pins "
				   "FROM orderable o "
				   "INNER JOIN device d ON (d.model = o.device_id) "
				   "WHERE d.datasheet_id = ? "
				   "GROUP BY o.drawing, o.pins "
				   "ORDER BY o.drawing ASC, o.pins ASC";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	int rc = sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	assert(SQLITE_OK == rc);

	vector<Package> result;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		string drw = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
		int pins = sqlite3_column_int(stmt, 1);
		result.push_back(Package{drw, pins});
	}
	sqlite3_reset(stmt);

	return result;
}

vector<Pinset> findPinsetsByDatasheet(sqlite3 *db, const string datasheetId) {
	static const char *SSET_QUERY = "SELECT signalset_id, idx, signal_id "
					"FROM signalset ss "
					"INNER JOIN signalset_signal sss ON ss.id = sss.signalset_id "
					"WHERE ss.id IN ( "
					"	SELECT signalset_id "
					"	FROM orderable o "
					"	INNER JOIN device d ON o.device_id = d.model "
					"	INNER JOIN pinset_signalset pss ON o.pinset_id = pss.pinset_id "
					"	WHERE d.datasheet_id = ? "
					"	GROUP BY signalset_id) "
					"ORDER BY signalset_id, idx ASC";

	static const char *PSET_QUERY = "SELECT pss.pinset_id, pss.signalset_id,pin_bga_row, pin_number "
					"from pinset_signalset pss "
					"WHERE pss.pinset_id IN ( "
					"	SELECT o.pinset_id "
					"	FROM orderable o "
					"	INNER JOIN device d ON o.device_id = d.model "
					"	WHERE d.datasheet_id = ?) "
					"ORDER BY pss.pinset_id ASC";

	static sqlite3_stmt *ssetStmt, *psetStmt;
	if ( ssetStmt == nullptr ) { // assume both are null
		prepare(db, &ssetStmt, SSET_QUERY);
		prepare(db, &psetStmt, PSET_QUERY);
	}

	sqlite3_reset(ssetStmt);
	sqlite3_reset(psetStmt);
	int rc;
	rc = sqlite3_bind_text(ssetStmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	assert(SQLITE_OK == rc);
	rc = sqlite3_bind_text(psetStmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	assert(SQLITE_OK == rc);

	unordered_map<int, Signalset *> sg; // id->signal set
	int lastId = 0, id;
	Signalset *s;
	while ( sqlite3_step(ssetStmt) == SQLITE_ROW ) {
		id = sqlite3_column_int(ssetStmt, 0);
		if ( lastId != id ) {
			s = new Signalset;
			s->signals.resize(10); // max # of signals hardcoded ...
			s->id = id;
			lastId = id;
			sg[id] = s;
		}

		int idx = sqlite3_column_int(ssetStmt, 1);
		string key = string(reinterpret_cast<const char *>(sqlite3_column_text(ssetStmt, 2)));
		s->signals[idx] = key;
	}

	vector<Pinset> ps;
	lastId = 0;
	Pinset p;
	while ( sqlite3_step(psetStmt) == SQLITE_ROW ) {
		id = sqlite3_column_int(psetStmt, 0);
		if ( lastId != id ) {
			ps.push_back(p);
			p = Pinset{.id = id};
			lastId = id;
		}
		int sgnStId = sqlite3_column_int(psetStmt, 1);
		const unsigned char *bgaRow = sqlite3_column_text(psetStmt, 2);
		Pin key;
		if ( bgaRow != nullptr ) {
			key.bgaRow = string(reinterpret_cast<const char *>(bgaRow));
		}
		key.number = sqlite3_column_int(psetStmt, 3);
		p.signalsets[key] = sg[sgnStId];
	}

	return ps;
}

unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db) {
	static const char *QUERY = "SELECT model, datasheet_id FROM device";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	unordered_map<string, string> result;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		string model = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
		string datasheet = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
		result[model] = datasheet;
	}
	return result;
}

unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db) {
	static const char *QUERY = "SELECT id, desc FROM signal";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}
	sqlite3_reset(stmt);

	unordered_map<string, string> result;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		string name = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
		string desc = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
		result[name] = desc;
	}
	return result;
}

/* Modify data in DB */

int saveSignals(sqlite3 *db, unordered_map<string, string> signals) {
	static const char *QUERY = "INSERT INTO SIGNAL(id, desc) VALUES (?1, ?2);";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		int rc = sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL);
		assert(SQLITE_OK == rc);
	}

	int insertedRows = 0, rc;
	for ( const std::pair<string, string> &signal : signals ) {
		sqlite3_reset(stmt);
		rc = sqlite3_bind_text(stmt, 1, signal.first.c_str(), -1, SQLITE_STATIC);
		assert(SQLITE_OK == rc);
		rc = sqlite3_bind_text(stmt, 2, signal.second.c_str(), -1, SQLITE_STATIC);
		assert(SQLITE_OK == rc);

		// execute, ignore errors for duplicates but reset statement (no longer mandatory, but good practice)
		if ( SQLITE_ROW == sqlite3_step(stmt) ) {
			insertedRows++;
		}
	}

	return insertedRows;
}

}}}} // namespace sjabloon430::tools::pinout::db
