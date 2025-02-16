#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>

struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
	int packages;
};

DatabaseTotals retrieveDBCounts(sqlite3 *db);
void importDatabase(sqlite3 *db, const std::filesystem::path &dbDir, std::function<void(const std::string &file, const char *error)> callback);

#endif // DATABASE_HPP
