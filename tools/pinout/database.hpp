#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>

namespace sjabloon430 { namespace tools { namespace db {

/** Support structs/classes */
struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
	int packages;
};

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

DatabaseTotals retrieveDBCounts(sqlite3 *db);

}}} // namespace sjabloon430::tools::db
#endif // DATABASE_HPP
