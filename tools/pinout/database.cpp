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

}}} // namespace sjabloon430::tools::db
