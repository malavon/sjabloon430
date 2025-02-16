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
	const char *QUERY = "select 1, count(*) from datasheet\
		union select 2, count(*) from device \
		union select 3, count(*) from package \
		union select 4, count(*) from orderable;";
	// I remember doing at work (Oracle) something with some sort of dummy table

	sqlite3_stmt *stmt;
	DatabaseTotals totals;
	totals.datasheets = -1;
	totals.devices = -1;
	totals.orderables = -1;
	totals.packages = -1;

	if ( sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL) != SQLITE_OK ) {
		std::cout << "SQLite3 error " << sqlite3_errmsg(db) << std::endl;
	} else {
		while ( sqlite3_step(stmt) == SQLITE_ROW ) {
			int det = sqlite3_column_int(stmt, 0);
			int count = sqlite3_column_int(stmt, 1);
			switch ( det ) {
				case 1:
					totals.datasheets = count;
					break;
				case 2:
					totals.devices = count;
					break;
				case 3:
					totals.packages = count;
					break;
				case 4:
					totals.orderables = count;
					break;
				default:
					std::cout << "ERROR: SQL result unknown: " << det << std::endl;
			}
		}
	}

	return totals;
}

}}}} // namespace sjabloon430::tools::pinout::db
