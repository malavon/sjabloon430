#include "database.hpp"

#include <iostream>

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

DatabaseTotals retrieveDBCounts(sqlite3 *db) {
	// something tells me there is an easier method of
	// aggregating these 4 counts in a single result row ...
	const char *QUERY = "select * from "
			    "(	select 'datasheet' as ordr, count(*) from datasheet"
			    "	union select 'device', count(*) from device"
			    "	union select 'orderable', count(*) from orderable"
			    "	union select 'package', count(*) from package"
			    ") order by ordr asc;";
	// I remember doing at work (Oracle) something with some sort of dummy table

	sqlite3_stmt *stmt;
	DatabaseTotals totals = {-1, -1, -1, -1};

	if ( sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL) != SQLITE_OK ) {
		std::cout << "SQLite3 error " << sqlite3_errmsg(db) << std::endl;
	} else {
		if ( sqlite3_step(stmt) == SQLITE_ROW ) {
			totals.datasheets = sqlite3_column_int(stmt, 1);
		}
		if ( sqlite3_step(stmt) == SQLITE_ROW ) {
			totals.devices = sqlite3_column_int(stmt, 1);
		}
		if ( sqlite3_step(stmt) == SQLITE_ROW ) {
			totals.orderables = sqlite3_column_int(stmt, 1);
		}
		if ( sqlite3_step(stmt) == SQLITE_ROW ) {
			totals.packages = sqlite3_column_int(stmt, 1);
		}
	}

	return totals;
}

}}}} // namespace sjabloon430::tools::pinout::db
