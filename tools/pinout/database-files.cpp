#include "database-files.hpp"

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>

#include "database.hpp" // included for db::prepare(), preparing sqlite3 statement

#ifndef DB_DIRECTORY
  #error "add -DDB_DIRECTORY=\"...\" to the compiler command line"
#endif

using namespace std;
using namespace std::filesystem;

namespace sjabloon430 { namespace tools { namespace db {

string insertStringFromResultSet(sqlite3_stmt *stmt) {
	int columns = sqlite3_column_count(stmt);
	if ( columns == 0 ) {
		return "ERROR NO COLUMNS";
	}

	const char *table = sqlite3_column_table_name(stmt, 0);
	string insert = "INSERT INTO ";
	insert += table;
	insert += " (";
	for ( int c = 0; c < columns; c++ ) {
		const char *origin = sqlite3_column_origin_name(stmt, c); // column name from DB
		if ( origin == nullptr ) {
			const char *col = sqlite3_column_name(stmt, c); // column name from AS-statement
			insert += col == nullptr ? "ERROR_NO_COL_NAME" : col;
		} else {
			insert += origin;
		}
		insert += ", ";
	}
	insert.erase(insert.size() - strlen(", ")); // remove last ", "
	insert += ") VALUES (";

	columns = sqlite3_data_count(stmt); // let's hope it's the same as before ...
	// TODO: values
	for ( int c = 0; c < columns; c++ ) {
		const char *type = sqlite3_column_decltype(stmt, c);
		const unsigned char *value = sqlite3_column_text(stmt, c);
		if ( value == nullptr ) {
			insert += "NULL";
		} else if ( strcmp(type, "INTEGER") == 0 || strcmp(type, "FLOAT") == 0 ) {
			insert += reinterpret_cast<const char *>(value);
		} else {
			insert += "'";
			insert += reinterpret_cast<const char *>(value);
			insert += "'";
		}
		insert += ", ";
	}
	insert.erase(insert.size() - strlen(", ")); // remove last ", "
	insert += ");";

	return insert;
}

// creates an update string from a resultset, first column is required to be the key on which to update!
string updateStringFromResultSet(sqlite3_stmt *stmt) {
	int columns = sqlite3_column_count(stmt);
	if ( columns <= 1 ) {
		return "ERROR NOT ENOUGH COLUMNS";
	}

	const char *table = sqlite3_column_table_name(stmt, 0);
	string sql = "UPDATE ";
	sql += table;
	string updates = " SET ";
	string condition = " WHERE ";

	columns = sqlite3_data_count(stmt); // let's hope it's the same as before ...
	// TODO: values
	string sub;
	for ( int c = 0; c < columns; c++ ) {
		sub = (c > 1) ? "," : ""; // first is id, second is first update, only second update requires a comma
		const char *origin = sqlite3_column_origin_name(stmt, c); // column name from DB
		if ( origin == nullptr ) {
			const char *col = sqlite3_column_name(stmt, c); // column name from AS-statement
			sub += (col == nullptr) ? "ERROR_NO_COL_NAME" : col;
		} else {
			sub += origin;
		}
		sub += " = ";
		const char *type = sqlite3_column_decltype(stmt, c);
		const unsigned char *value = sqlite3_column_text(stmt, c);
		if ( value == nullptr ) {
			sub += "NULL"; // only allowed for updates, not condition ...
		} else if ( strcmp(type, "INTEGER") == 0 || strcmp(type, "FLOAT") == 0 ) {
			sub += reinterpret_cast<const char *>(value);
		} else {
			sub += "'";
			sub += reinterpret_cast<const char *>(value);
			sub += "'";
		}

		if ( c == 0 ) {
			condition += sub;
		} else {
			updates += sub;
		}
	}

	return sql + updates + condition + ";";
}

void exportFromPrepStmt(sqlite3_stmt *stmt, const string fileName, const ExportConfig &config) {
	std::filesystem::path outFile(DB_DIRECTORY);
	outFile /= fileName;
	std::ofstream out(outFile, config.appendFile ? (ios::out | ios::app) : ios::out); // output & append (todo)
	// insert a comment in the file, unless appending
	if ( config.appendFile ) {
		out << endl; // todo: some custom comment? table name? difficult
	} else {
		out << "--" << endl;
		out << "-- File generated with one of the sjabloon 430 database tools." << endl;
		out << "-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid." << endl;
		out << "-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL." << endl;
		out << "--" << endl;
		out << "-- Text encoding used: UTF-8" << endl;
		out << "--" << endl;
	}
	if ( config.tx == ExportConfig::Tx::BOTH || config.tx == ExportConfig::Tx::BEGIN ) {
		out << "BEGIN TRANSACTION;" << endl << endl;
	}

	while ( SQLITE_ROW == sqlite3_step(stmt) ) {
		if ( config.sql == ExportConfig::SQL::INSERT ) {
			out << insertStringFromResultSet(stmt) << endl;
		} else {
			out << updateStringFromResultSet(stmt) << endl;
		}
	}

	if ( config.tx == ExportConfig::Tx::BOTH || config.tx == ExportConfig::Tx::COMMIT ) {
		out << endl << "COMMIT TRANSACTION;" << endl;
	}
	sqlite3_finalize(stmt);
	out.close();
}

// sub-functions for exports of pinout data
void exportPinoutSignalsets(sqlite3 *db, const string &datasheetId, const string filename, ExportConfig expConf) {
	static const char *QUERY = "SELECT ss.* "
				   "FROM signalset ss "
				   "INNER JOIN pinset_signalset psss ON psss.signalset_id = ss.id "
				   "INNER JOIN pinset ps ON ps.id = psss.pinset_id "
				   "WHERE ps.id IN ("
				   "	SELECT pinset_id "
				   "	FROM orderable o "
				   "	INNER JOIN device d ON d.model = o.device_id "
				   "	WHERE datasheet_id = ? "
				   "	GROUP BY pinset_id) "
				   "GROUP BY ss.id "
				   "ORDER BY datasheet_idx ASC"; // no other columns needed, only 1 datasheet
	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	exportFromPrepStmt(stmt, filename, expConf);
}

void exportPinoutSignalsetSignalLinks(sqlite3 *db, const string &datasheetId, const string filename, ExportConfig expConf) {
	static const char *QUERY = "SELECT sss.signalset_id, sss.idx, sss.signal_id "
				   "FROM signalset_signal sss "
				   "INNER JOIN signalset ss ON ss.id = sss.signalset_id "
				   "INNER JOIN pinset_signalset psss ON psss.signalset_id = ss.id "
				   "WHERE psss.pinset_id IN ("
				   "	SELECT pinset_id "
				   "	FROM orderable o "
				   "	INNER JOIN device d ON d.model = o.device_id "
				   "	WHERE datasheet_id = ? "
				   "	GROUP BY pinset_id) "
				   "GROUP BY sss.signalset_id, sss.signal_id "
				   "ORDER BY sss.signalset_id ASC, sss.idx ASC";
	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	exportFromPrepStmt(stmt, filename, expConf);
}

void exportPinoutPinsets(sqlite3 *db, const string &datasheetId, const string filename, ExportConfig expConf) {
	static const char *QUERY = "SELECT ps.* "
				   "FROM pinset ps "
				   "WHERE id IN ( "
				   "	SELECT pinset_id "
				   "	FROM orderable o "
				   "	INNER JOIN device d ON d.model = o.device_id "
				   "	WHERE datasheet_id = ?) "
				   "ORDER BY id ASC";
	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	exportFromPrepStmt(stmt, filename, expConf);
}

void exportPinoutPinsetSignalsetLinks(sqlite3 *db, const string &datasheetId, const string filename, ExportConfig expConf) {
	static const char *QUERY = "SELECT psss.* "
				   "FROM pinset_signalset psss "
				   "INNER JOIN pinset ps ON ps.id = psss.pinset_id "
				   "WHERE ps.id IN ("
				   "	SELECT pinset_id "
				   "	FROM orderable o "
				   "	INNER JOIN device d ON d.model = o.device_id "
				   "	WHERE datasheet_id = ?) "
				   "ORDER BY pinset_id ASC, signalset_id ASC, pin_bga_row ASC, pin_number ASC";
	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	exportFromPrepStmt(stmt, filename, expConf);
}

void exportPinoutPinsetOrderableLinks(sqlite3 *db, const string &datasheetId, const string filename, ExportConfig expConf) {
	// order on pinset_id is first because they're grouped together
	// order including d.model because names are not always logical
	static const char *QUERY = "SELECT name, pinset_id "
				   "FROM orderable o "
				   "INNER JOIN device d ON d.model = o.device_id "
				   "WHERE pinset_id IS NOT NULL "
				   "AND d.datasheet_id = ? "
				   "ORDER BY pinset_id ASC, d.model ASC, o.name ASC";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, datasheetId.c_str(), -1, SQLITE_STATIC);
	exportFromPrepStmt(stmt, filename, expConf);
}

void exportPinoutData(sqlite3 *db, const string &datasheetId) {
	string lower = datasheetId; // is there no single-function for strings or even const char*??
	for ( char &c : lower ) {
		c = std::tolower(c);
	}
	const string file = "99_" + lower + ".sql";
	exportPinoutSignalsets(db, datasheetId, file, ExportConfig{.appendFile = false, .tx = ExportConfig::Tx::BEGIN});
	exportPinoutSignalsetSignalLinks(db, datasheetId, file, ExportConfig{.appendFile = true, .tx = ExportConfig::Tx::NONE});
	exportPinoutPinsets(db, datasheetId, file, ExportConfig{.appendFile = true, .tx = ExportConfig::Tx::NONE});
	exportPinoutPinsetSignalsetLinks(db, datasheetId, file, ExportConfig{.appendFile = true, .tx = ExportConfig::Tx::NONE});
	exportPinoutPinsetOrderableLinks(
	    db, datasheetId, file,
	    ExportConfig{.appendFile = true, .tx = ExportConfig::Tx::COMMIT, .sql = ExportConfig::SQL::UPDATE});
}

void exportSignals(sqlite3 *db) {
	static const char *QUERY = "SELECT signalgroup, id, desc FROM signal ORDER BY signalgroup ASC, id ASC";
	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		prepare(db, &stmt, QUERY);
	}

	exportFromPrepStmt(stmt, "24_signal.sql");
}

// maybe this should be a function shared with other programs
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback) {
	std::filesystem::path dbDir(DB_DIRECTORY);
	// iterate all files, sort alphabetically/numerically and check if it's actually a (SQL) file
	// TODO: recursive, should also include pinout per device later, simplifies files
	set<path> files;
	directory_iterator it(dbDir);
	for ( const directory_entry &dir_entry : it ) {
		if ( dir_entry.is_regular_file() && dir_entry.path().extension() == ".sql" ) {
			files.insert(dir_entry.path());
		}
	}

	// insert all files into in-memory DB
	int l = 20;
	for ( const path &p : files ) {
		// read file completely into memory
		std::ifstream input(p);
		std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

		char *errorMsg;
		sqlite3_exec(db, content.c_str(), nullptr /*NULL callback is valid?*/, nullptr, &errorMsg);

		if ( errorMsg == nullptr ) {
			callback(p.filename(), nullptr);
		} else {
			callback(p.filename(), errorMsg);
			sqlite3_free(errorMsg);
		}
	}
}

}}} // namespace sjabloon430::tools::db
