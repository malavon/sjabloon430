#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>

namespace sjabloon430 { namespace tools { namespace db {

struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
	int packages;
};

void importDatabase(sqlite3 *db, const std::filesystem::path &dbDir, std::function<void(const std::string &file, const char *error)> callback);

/* Query DB */
DatabaseTotals countTotals(sqlite3 *db);

}}}
#endif // DATABASE_HPP
