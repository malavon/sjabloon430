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

// Data modifications

int saveOrUpdate(sqlite3 *db, const Datasheet &ds) {
	static const char *INSERT = "INSERT INTO "
				    "datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) "
				    "VALUES (:id, :rev, :imonth, :iyear, :rmonth, :ryear, 'MASS IMPORT FROM TSV')";
	static const char *UPDATE = "UPDATE datasheet "
				    "SET revision = ?, issue_month = ?, issue_year = ?, rev_month = ?, rev_year = ? "
				    "WHERE id = ? ";
	static sqlite3_stmt *insStmt, *updStmt;
	if ( insStmt == nullptr ) { // assume both are null
		prepare(db, &insStmt, INSERT);
		prepare(db, &updStmt, UPDATE);
	}

	int alteredRows = 0, pm = 0;
	std::array<int, 7> rc;

	// make it simple: do an update first, if nothing updated, insert
	sqlite3_reset(updStmt);
	rc[pm] = sqlite3_bind_text(updStmt, ++pm, ds.rev.c_str(), -1, SQLITE_STATIC);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, ds.issued.month);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, ds.issued.year);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, ds.revised.month);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, ds.revised.year);

	rc[pm] = sqlite3_bind_text(updStmt, ++pm, ds.id.c_str(), -1, SQLITE_STATIC);
	std::for_each(rc.begin() + 1, rc.end(), [](int n) { assert(n == SQLITE_OK); });
	rc[pm] = sqlite3_step(updStmt);
	assert(SQLITE_DONE == rc[pm]);
	alteredRows += sqlite3_changes(db);

	if ( alteredRows == 0 ) { // updated nothing, insert then
		pm = 0;
		sqlite3_reset(insStmt);
		rc[pm] = sqlite3_bind_text(insStmt, ++pm, ds.id.c_str(), -1, SQLITE_STATIC);
		rc[pm] = sqlite3_bind_text(insStmt, ++pm, ds.rev.c_str(), -1, SQLITE_STATIC);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, ds.issued.month);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, ds.issued.year);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, ds.revised.month);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, ds.revised.year);
		std::for_each(rc.begin() + 1, rc.end(), [](int n) { assert(n == SQLITE_OK); });
		if ( SQLITE_DONE == sqlite3_step(insStmt) ) {
			alteredRows += sqlite3_changes(db);
		}
	}
	return alteredRows;
}

}}}} // namespace sjabloon430::tools::device::db
