
#include "database.hpp"

#include <algorithm>
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

sqlite3 *createDatabase() {
	sqlite3 *db;
	// in-memory is preferred, but exporting should be simple, formatted and not DIY
	// if not, use a file database?
	unsigned int rc = sqlite3_open("file::memory:", &db);

	if ( rc != 0 ) {
		sqlite3_close(db);
		db = nullptr;
	}
	return db;
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

/* Query DB */

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
		int rc = sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL);
		if ( rc != SQLITE_OK ) {
			cerr << "SQLite3 error " << sqlite3_errmsg(db) << endl;
		}
		assert(rc == SQLITE_OK);
	}

	DatabaseTotals totals;
	totals.datasheets = -1;
	totals.devices = -1;
	totals.orderables = -1;
	totals.packages = -1;

	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		totals.datasheets = sqlite3_column_int(stmt, 0);
		totals.devices = sqlite3_column_int(stmt, 1);
		totals.orderables = sqlite3_column_int(stmt, 2);
		totals.packages = sqlite3_column_int(stmt, 3);
	}

	return totals;
}

Datasheet findDatasheetByModel(sqlite3 *db, const string model) {
	static const char *QUERY = "SELECT datasheet FROM device WHERE model='?'";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) {
		// a single result row is best, 1 column per count
		// this is the best I can do with my knowledge of sqlite
		int rc = sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL);
		if ( rc != SQLITE_OK ) {
			cerr << "SQLite3 error " << sqlite3_errmsg(db) << endl;
		}
		assert(rc == SQLITE_OK);
	}

	sqlite3_reset(stmt);
	sqlite3_bind_text(stmt, 1, model.c_str(), -1, SQLITE_STATIC);

	// assume only a single row
	Datasheet ds;
	if ( sqlite3_step(stmt) == SQLITE_ROW ) {
		ds.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
	}
	return ds;
}

}}} // namespace sjabloon430::tools::db
