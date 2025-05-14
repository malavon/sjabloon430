#ifndef SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
#define SJABLOON430_TOOLS_PINOUT_DATABASE_HPP

#include <sqlite3.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace sjabloon430 { namespace tools { namespace pinout { namespace db {

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

struct Package {
	string drawing;
	int pins;
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);
Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db);
unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db);

/* Modify DB, inserts return inserted rows */
int saveSignals(sqlite3 *db, unordered_map<string, string> signals);

}}}} // namespace sjabloon430::tools::pinout::db
#endif // SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
