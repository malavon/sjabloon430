#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

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
	string issueDate;
	string revDate;
};

struct Package {
	string drawing;
	int pins;
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db);
unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db);

}}} // namespace sjabloon430::tools::db
#endif // DATABASE_HPP
