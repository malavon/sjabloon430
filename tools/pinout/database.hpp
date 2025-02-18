#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>
#include <vector>

namespace sjabloon430 { namespace tools { namespace db {

using namespace std;

/** Support structs/classes */
struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
	int packages;
};

/* Simple data objects, no need for encapsulation in a privately used tool ... */
struct Datasheet {
	string id;
	string rev;
	string origDate;
	string revDate;
};

void importDatabase(sqlite3 *db, const filesystem::path &dbDir, function<void(const string &file, const char *error)> callback);

/* Query DB */
Datasheet findDatasheetByModel(sqlite3 *db, const string model);

vector<string> listDatasheetIds(sqlite3 *db, const string firstChars);
vector<string> listModels(sqlite3 *db, const string firstChars);

DatabaseTotals countTotals(sqlite3 *db);

}}}
#endif // DATABASE_HPP
