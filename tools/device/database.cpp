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

/* Queries */

template<>
vector<Datasheet> findAll<Datasheet>(sqlite3 *db) {
	static const char *QUERY = "SELECT id, revision, issue_month, issue_year, rev_month, rev_year "
				   "FROM datasheet "
				   "ORDER BY id ASC";

	static sqlite3_stmt *stmt;
	if ( stmt == nullptr ) { // assume both are null
		prepare(db, &stmt, QUERY);
	}

	sqlite3_reset(stmt);
	vector<Datasheet> result;
	int i;
	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		Datasheet ds;
		i = 0;
		ds.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i++));
		ds.rev = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i++));
		ds.issued.month = sqlite3_column_int(stmt, i++);
		ds.issued.year = sqlite3_column_int(stmt, i++);
		ds.revised.month = sqlite3_column_int(stmt, i++);
		ds.revised.year = sqlite3_column_int(stmt, i++);
		result.push_back(ds);
	}
	return result;
}

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

int saveOrUpdate(sqlite3 *db, const Device &dv) {
	static const char *INSERT = "INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, "
				    "gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, "
				    "op_temp_min, op_temp_max, comment) "
				    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 'TI EXPORT')";
	static const char *UPDATE = "UPDATE device "
				    "SET datasheet_id = ?, "
				    "freq_max = ?, storage_bytes = ?, ram_bytes = ?, "
				    "gpio_count = ?, uart_count = ?, usb_count = ?, i2c_count = ?, spi_count = ?, "
				    "comp_count = ?, timer_count = ?, "
				    "op_temp_min = ?, op_temp_max = ? "
				    "WHERE model = ? ";
	static sqlite3_stmt *insStmt, *updStmt;
	if ( insStmt == nullptr ) { // assume both are null
		prepare(db, &insStmt, INSERT);
		prepare(db, &updStmt, UPDATE);
	}

	int alteredRows = 0, pm = 0;
	std::array<int, 15> rc;
	// make it simple: do an update first, if nothing updated, insert

	sqlite3_reset(updStmt);
	rc[pm] = sqlite3_bind_text(updStmt, ++pm, dv.datasheetId.c_str(), -1, SQLITE_STATIC);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.maxFreq);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.storage);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.ram);

	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.ngpio);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.nuart);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.nusb);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.ni2c);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.nspi);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.ncomp);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.ntimer);

	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.opTempMin);
	rc[pm] = sqlite3_bind_int(updStmt, ++pm, dv.opTempMax);

	rc[pm] = sqlite3_bind_text(updStmt, ++pm, dv.model.c_str(), -1, SQLITE_STATIC);
	std::for_each(rc.begin() + 1, rc.begin() + 1 + pm, [](int n) { assert(n == SQLITE_OK); });
	rc[pm] = sqlite3_step(updStmt);
	assert(SQLITE_DONE == rc[pm]);
	alteredRows += sqlite3_changes(db);

	if ( alteredRows == 0 ) { // updated nothing, insert then
		pm = 0;
		sqlite3_reset(insStmt);
		rc[pm] = sqlite3_bind_text(insStmt, ++pm, dv.model.c_str(), -1, SQLITE_STATIC);
		rc[pm] = sqlite3_bind_text(insStmt, ++pm, dv.datasheetId.c_str(), -1, SQLITE_STATIC);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.maxFreq);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.storage);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.ram);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.ngpio);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.nuart);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.nusb);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.ni2c);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.nspi);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.ncomp);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.ntimer);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.opTempMin);
		rc[pm] = sqlite3_bind_int(insStmt, ++pm, dv.opTempMax);
		std::for_each(rc.begin() + 1, rc.begin() + 1 + pm, [](int n) { assert(n == SQLITE_OK); });
		if ( SQLITE_DONE == sqlite3_step(insStmt) ) {
			alteredRows += sqlite3_changes(db);
		}
	}
	return alteredRows;
}
}}}} // namespace sjabloon430::tools::device::db
