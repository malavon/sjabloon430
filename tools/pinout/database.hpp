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

struct Package {
	string drawing;
	int pins;

	bool operator==(const Package &o) const {
		return drawing == o.drawing && pins == o.pins;
	}
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();
// helper function to prepare a sqlite3 statement
void prepare(sqlite3 *db, sqlite3_stmt **stmt, const char *query);

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db);
unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db);

/* Modify DB, inserts return inserted rows */
int saveSignals(sqlite3 *db, unordered_map<string, string> signals);

}}} // namespace sjabloon430::tools::db

template<>
struct std::hash<sjabloon430::tools::db::Package> {
	std::size_t operator()(const sjabloon430::tools::db::Package &p) const noexcept {
		std::size_t h1 = std::hash<std::string>{}(p.drawing);
		std::size_t h2 = p.pins;
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

#endif // SJABLOON430_TOOLS_DATABASE_HPP
