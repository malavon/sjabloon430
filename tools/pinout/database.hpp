#ifndef SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
#define SJABLOON430_TOOLS_PINOUT_DATABASE_HPP

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

	operator const string() const {
		return bgaRow + (number == 0 ? "" : std::to_string(number));
	}
};

struct Package {
	string drawing;
	int pins;
	bool operator==(const Package &o) const {
		return drawing == o.drawing && pins == o.pins;
	}
	bool operator!=(const Package &o) const { // for comparison with iterators
		return drawing != o.drawing || pins != o.pins;
	}
	bool operator<(const Package &o) const { // for addition to (ordered) std::set
		return drawing < o.drawing || (pins < o.pins && drawing == o.drawing);
	}
	operator const string() const { // for consistency and ease-of-use
		return drawing + std::to_string(pins);
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

namespace sjabloon430 { namespace tools { namespace pinout { namespace db {

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
	string model;
	Package pkg;
	int pinsetId; // link?
};

struct Pinset {
	int id = 0; // auto-increment
	int totalPins = 0;
	unordered_map<Pin, struct Signalset> signalsets = {};
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

int saveOrUpdatePinset(sqlite3 *db, Pinset &ps);		  // assumes signalsets are all in DB!
int saveOrUpdateSignalsets(sqlite3 *db, vector<Signalset> &sets); // assumes signals are all in DB!
int saveSignals(sqlite3 *db, unordered_map<string, string> signals);

}}}} // namespace sjabloon430::tools::pinout::db

#endif // SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
