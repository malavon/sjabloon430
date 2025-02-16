
#include "database.hpp"

#include <algorithm>
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
	DatabaseTotals totals;
	totals.datasheets = -1;
	totals.devices = -1;
	totals.orderables = -1;
	totals.packages = -1;

	if ( sqlite3_prepare_v2(db, QUERY, -1, &stmt, NULL) != SQLITE_OK ) {
		cout << "SQLite3 error " << sqlite3_errmsg(db) << endl;
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

}}} // namespace sjabloon430::tools::db
