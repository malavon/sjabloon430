#ifndef SJABLOON430_TOOLS_DATABASE_HPP
#define SJABLOON430_TOOLS_DATABASE_HPP

#include <sqlite3.h>

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

namespace sjabloon430 { namespace tools {

/* Simple data objects which are not really database-related */
struct Pin {
	string bgaRow;
	int number;

	bool empty() const {
		return bgaRow.empty() && number <= 0;
	}

	bool operator==(const Pin &o) const {
		return bgaRow == o.bgaRow && number == o.number;
	}
};

struct Package {
	string drawing;
	int pins;
	bool operator==(const Package &o) const {
		return drawing == o.drawing && pins == o.pins;
	}
};
}} // namespace sjabloon430::tools

template<>
struct std::hash<sjabloon430::tools::Package> {
	std::size_t operator()(const sjabloon430::tools::Package &p) const noexcept {
		std::size_t h1 = std::hash<std::string>{}(p.drawing);
		std::size_t h2 = p.pins;
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

template<>
struct std::hash<sjabloon430::tools::Pin> {
	std::size_t operator()(const sjabloon430::tools::Pin &p) const noexcept {
		std::size_t h1 = std::hash<std::string>{}(p.bgaRow);
		std::size_t h2 = p.number;
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

namespace sjabloon430 { namespace tools { namespace db {

/** Support structs/classes */
struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
};

/* Simple data objects, no need for encapsulation in a privately used tool ... */
struct Datasheet {
	string id;
	string rev;
	string issueDate;
	string revDate;
};

struct Orderable {
	string name; // also id (never linked to... useless)
	Package pkg;
	int pinsetId; // link?
};

struct Pinset {
	int id = 0; // auto-increment
	int totalPins;
	unordered_map<Pin, struct Signalset> signalsets;
};

struct Signalset {
	int id = 0;	  // auto-increment
	int parentId = 0; // 0 == NULL
	vector<string> signals;
	unordered_map<Package, Pin> pins; // this construct can store only a single empty/null pin!
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();
// helper function to prepare a sqlite3 statement
void prepare(sqlite3 *db, sqlite3_stmt **stmt, const char *query);

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);
DatabaseTotals countSupported(sqlite3 *db);

Datasheet findDatasheet(sqlite3 *db, const string id);
vector<string> findModelsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Orderable> findOrderablesByDatasheet(sqlite3 *db, const string datasheetId);
vector<Package> findPackagesByDatasheet(sqlite3 *db, const string datasheetId);
vector<Pinset> findPinsetsByDatasheet(sqlite3 *db, const string datasheetId);
vector<Signalset> findSignalsetsByDatasheet(sqlite3 *db, const string datasheetId);
unordered_map<string, string> listAllModelsAndDatasheets(sqlite3 *db);
unordered_map<string, string> listAllSignalDescriptions(sqlite3 *db);

/* Modify DB, inserts return inserted rows */
int linkOrderableToPinset(sqlite3 *, const vector<Orderable> &);

int saveSignals(sqlite3 *db, unordered_map<string, string> signals);
int saveSignalsets(sqlite3 *db, vector<Signalset> &sets); // assumes signals are all in DB!
int saveOrUpdatePinset(sqlite3 *db, Pinset &ps);	  // assumes signal sets are all in DB!

}}} // namespace sjabloon430::tools::db

#endif // SJABLOON430_TOOLS_DATABASE_HPP
