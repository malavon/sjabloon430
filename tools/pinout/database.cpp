#include "database.hpp"

#include <cassert>
#include <iostream>
#include <set>

namespace sjabloon430 { namespace tools { namespace db {

sqlite3 *createDatabase() {
	sqlite3 *db;
	// in-memory is preferred, but exporting should be simple, formatted and not DIY
	// if not, use a file database?
	// unsigned int rc = sqlite3_open("file:debug.db", &db);
	unsigned int rc = sqlite3_open("file::memory:", &db);

	if ( rc != 0 ) {
		sqlite3_close(db);
		db = nullptr;
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
	static const char *QUERY = "SELECT SUM(datasheets), SUM(devices), SUM(orderables), SUM(packages) "
				   "FROM ("
				   "	SELECT 0 AS datasheets, 0 AS devices, 0 AS orderables, 0 AS packages"
				   "	UNION SELECT COUNT(*), 0, 0, 0 FROM datasheet"
				   "	UNION SELECT 0, COUNT(*), 0, 0 FROM device"
				   "	UNION SELECT 0, 0, COUNT(*), 0 FROM orderable"
				   "	UNION SELECT 0, 0, 0, COUNT(*) FROM package )";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	DatabaseTotals totals{-1, -1, -1, -1};

	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		totals.datasheets = sqlite3_column_int(stmt, 0);
		totals.devices = sqlite3_column_int(stmt, 1);
		totals.orderables = sqlite3_column_int(stmt, 2);
		totals.packages = sqlite3_column_int(stmt, 3);
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

vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId) {
	static const char *QUERY = "SELECT o.drawing, o.pins "
				   "FROM orderable o "
				   "INNER JOIN device d ON (d.model = o.device_id) "
				   "WHERE d.datasheet_id = ? "
				   "GROUP BY o.drawing, o.pins "
				   "ORDER BY o.pins DESC";

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

}}} // namespace sjabloon430::tools::db
