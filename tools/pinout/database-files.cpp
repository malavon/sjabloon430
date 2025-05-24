#include "database-files.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>

#ifndef DB_DIRECTORY
  #error "add -DDB_DIRECTORY=\"...\" to the compiler command line"
#endif

using namespace std;
using namespace std::filesystem;

namespace sjabloon430 { namespace tools { namespace db {

// privately used functions forward declarations

// export from a simple query, cannot export joined tables etc
void exportFromPrepStmt(sqlite3_stmt *statement, const string fileName, const ExportConfig &config = ExportConfig{});
string insertStringFromResultSet(sqlite3_stmt *stmt);
string updateStringFromResultSet(sqlite3_stmt *stmt, int whereColumns = 1);

// helper functions
void prepare(sqlite3 *db, sqlite3_stmt **stmt, const char *query) {
	int rc = sqlite3_prepare_v2(db, query, -1, stmt, NULL);
	if ( rc != SQLITE_OK ) {
		std::cerr << "SQLite3 error " << sqlite3_errmsg(db) << std::endl;
	}
	assert(rc == SQLITE_OK);
}

string insertStringFromResultSet(sqlite3_stmt *stmt) {
	const int columns = sqlite3_column_count(stmt);
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

	for ( int c = 0; c < columns; c++ ) {
		const char *type = sqlite3_column_decltype(stmt, c);
		const unsigned char *value = sqlite3_column_text(stmt, c);
		if ( value == nullptr ) {
			insert += "NULL";
		} else if ( strcmp(type, "INTEGER") == 0 || strcmp(type, "REAL") == 0 ) {
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
string updateStringFromResultSet(sqlite3_stmt *stmt, int whereColumns) {
	const int columns = sqlite3_column_count(stmt);
	if ( columns <= whereColumns ) {
		return "ERROR NOT ENOUGH COLUMNS";
	}

	const char *table = sqlite3_column_table_name(stmt, 0);
	string sql = "UPDATE ";
	sql += table;
	string updates = " SET ";
	string condition = " WHERE ";

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
		} else if ( strcmp(type, "INTEGER") == 0 || strcmp(type, "REAL") == 0 ) {
			sub += reinterpret_cast<const char *>(value);
		} else {
			sub += "'";
			sub += reinterpret_cast<const char *>(value);
			sub += "'";
		}

		if ( c < whereColumns ) {
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

	if ( !config.appendFile ) {
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

	int rc = sqlite3_step(stmt);
	while ( rc == SQLITE_ROW ) {
		if ( config.sql == ExportConfig::SQL::INSERT ) {
			out << insertStringFromResultSet(stmt) << endl;
		} else {
			out << updateStringFromResultSet(stmt) << endl;
		}
		if ( (rc = sqlite3_step(stmt)) == SQLITE_DONE ) { // one more endline AFTER block for this query
			out << endl;
		}
	}

	if ( config.tx == ExportConfig::Tx::BOTH || config.tx == ExportConfig::Tx::COMMIT ) {
		out << "COMMIT TRANSACTION;" << endl;
	}
	out.close();
}

void exportSignals(sqlite3 *db) {
	static const char *GROUPS = "SELECT * "
				    "FROM signalgroup "
				    "ORDER BY name";
	static const char *SIGNALS = "SELECT signalgroup, id, desc "
				     "FROM signal "
				     "ORDER BY signalgroup ASC, id ASC";
	static sqlite3_stmt *grpStmt, *sgnStmt;
	if ( sgnStmt == nullptr ) {
		prepare(db, &grpStmt, GROUPS);
		prepare(db, &sgnStmt, SIGNALS);
	}

	exportFromPrepStmt(grpStmt, "24_signal.sql", ExportConfig{.tx = ExportConfig::Tx::BEGIN});
	exportFromPrepStmt(sgnStmt, "24_signal.sql", ExportConfig{.appendFile = true, .tx = ExportConfig::Tx::COMMIT});
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
	for ( const path &p : files ) {
		// read file completely into memory
		std::ifstream input(p);
		std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

		char *errorMsg;
		sqlite3_exec(db, content.c_str(), nullptr /*NULL callback is valid?*/, nullptr, &errorMsg);

		if ( errorMsg == nullptr ) {
			callback(p.filename(), nullptr);
		} else {
			// rollback transaction; if there is no transaction, the error is ignored
			// without rolling back the current transaction, all following files will error, possibly without real cause
			sqlite3_exec(db, "ROLLBACK TRANSACTION;", nullptr, nullptr, nullptr);
			callback(p.filename(), errorMsg);
			sqlite3_free(errorMsg);
		}
	}
}

}}} // namespace sjabloon430::tools::db
