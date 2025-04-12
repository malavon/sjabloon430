#ifndef SJABLOON430_TOOLS_DATABASE_HPP
#define SJABLOON430_TOOLS_DATABASE_HPP

#include <sqlite3.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace sjabloon430 { namespace tools { namespace db {

using std::string;
using std::unordered_map;
using std::vector;

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
	string issueDate;
	string revDate;
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<string> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db);
unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db);

}}} // namespace sjabloon430::tools::db
#endif // SJABLOON430_TOOLS_DATABASE_HPP
