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
	bool operator==(const Package &o) const {
		return drawing == o.drawing && pins == o.pins;
	}
};

struct PinsetKey {
	int deviceId;
	Package pkg;
	bool operator==(const PinsetKey &o) const {
		return deviceId == o.deviceId && pkg == o.pkg;
	}
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();

// export from a simple query, cannot export joined tables etc
void exportFromPrepStmt(sqlite3_stmt *statement, const string fileName);
void exportSignals(sqlite3 *db);
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
// unordered_map<PinsetKey, int>
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
		return h2 ^ (h1 << 1);
	}
};

template<>
struct std::hash<sjabloon430::tools::db::PinsetKey> {
	std::size_t operator()(const sjabloon430::tools::db::PinsetKey &p) const noexcept {
		std::size_t h1 = std::hash<sjabloon430::tools::db::Package>{}(p.pkg);
		std::size_t h2 = p.deviceId;
		return h2 ^ (h1 << 1);
	}
};

#endif // DATABASE_HPP
