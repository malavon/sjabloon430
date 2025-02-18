#ifndef SJABLOON430_TOOLS_DATABASE_HPP
#define SJABLOON430_TOOLS_DATABASE_HPP

#include <sqlite3.h>

#include <string>

namespace sjabloon430 { namespace tools { namespace db {

using std::string;

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

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

}}} // namespace sjabloon430::tools::db
#endif // SJABLOON430_TOOLS_DATABASE_HPP
