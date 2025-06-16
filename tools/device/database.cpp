#include "database.hpp"

#include <cassert>
#include <iostream>

namespace sjabloon430 { namespace tools { namespace device { namespace db {

sqlite3 *createDatabase() {
	sqlite3 *db;
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

// helper function to prepare a sqlite3 statement
void prepare(sqlite3 *db, sqlite3_stmt **stmt, const char *QUERY) {
	int rc = sqlite3_prepare_v2(db, QUERY, -1, stmt, nullptr);
	if ( rc != SQLITE_OK ) {
		std::cerr << "SQLite3 error " << sqlite3_errmsg(db) << std::endl;
	}
	assert(rc == SQLITE_OK);
}

// QUERY functions

// SAVE/UPDATE functions

}}}} // namespace sjabloon430::tools::device::db
