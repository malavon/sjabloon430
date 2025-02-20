
#include "database.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>

#ifndef DB_DIRECTORY
#  error "add -DDB_DIRECTORY=\"...\" to the compiler command line"
#endif

using namespace std;
using namespace std::filesystem;

namespace sjabloon430 { namespace tools { namespace db {

// maybe this should be a function shared with other programs
void importDatabase(sqlite3 *db, const path &dbDir, std::function<void(const std::string &file, const char *error)> callback) {
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
	const char *QUERY = "SELECT SUM(datasheets), SUM(devices), SUM(orderables), SUM(packages) FROM ( \
							SELECT 0 AS datasheets, 0 AS devices, 0 AS orderables, 0 AS packages \
							UNION SELECT COUNT(*), 0, 0, 0 FROM datasheet \
							UNION SELECT 0, COUNT(*), 0, 0 FROM device \
							UNION SELECT 0, 0, COUNT(*), 0 FROM orderable \
							UNION SELECT 0, 0, 0, COUNT(*) FROM package )";
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
			totals.datasheets = sqlite3_column_int(stmt, 0);
			totals.devices = sqlite3_column_int(stmt, 1);
			totals.orderables = sqlite3_column_int(stmt, 2);
			totals.packages = sqlite3_column_int(stmt, 3);
		}
	}

	return totals;
}

Datasheet findDatasheet(sqlite3 *db, const string id) {
	static const string QUERY("SELECT id, revision, CONCAT(issue_month, '/', issue_year) issue_date,"
							  "CONCAT(rev_month, '/', rev_year) rev_date FROM datasheet WHERE id='");
	string query = QUERY + id + "'";
	sqlite3_stmt *stmt;
	// assume only a single row
	Datasheet ds;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	if ( rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW ) {
		ds.id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
		ds.rev = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
		ds.issueDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
		ds.revDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
	}
	return ds;
}

vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId) {
	static const string QUERY("SELECT model FROM device WHERE datasheet_id = '");
	string query = QUERY + datasheetId + "%'";

	vector<string> result;
	sqlite3_stmt *stmt;
	if ( sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK ) {
		while ( sqlite3_step(stmt) == SQLITE_ROW ) {
			result.push_back(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0))));
		}
	}
	return result;
}

vector<string> findPackagesByDatasheet(sqlite3 *db, const string datasheetId) {
	static const string QUERY("SELECT CONCAT(o.drawing, o.pins) pkg FROM orderable o "
							  "INNER JOIN device d ON (d.id = o.device_id) "
							  "WHERE d.datasheet_id = '");
	static const string QUERY2("' GROUP BY o.drawing, o.pins "
							   "ORDER BY o.pins DESC;");
	string query = QUERY + datasheetId + QUERY2;

	vector<string> result;
	sqlite3_stmt *stmt;
	if ( sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK ) {
		while ( sqlite3_step(stmt) == SQLITE_ROW ) {
			result.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
		}
	}
	return result;
}

unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db) {
	static const string QUERY("SELECT model, datasheet_id FROM device");

	sqlite3_stmt *stmt;
	unordered_map<string, string> result;
	if ( sqlite3_prepare_v2(db, QUERY.c_str(), -1, &stmt, NULL) == SQLITE_OK ) {
		while ( sqlite3_step(stmt) == SQLITE_ROW ) {
			string model = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
			string datasheet = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
			result[model] = datasheet;
		}
	}
	return result;
}

}}} // namespace sjabloon430::tools::db
