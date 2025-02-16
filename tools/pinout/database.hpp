#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>
#include <vector>

namespace sjabloon430 { namespace tools { namespace db {

/** Support structs/classes */
struct DatabaseTotals {
	int datasheets;
	int devices;
	int orderables;
	int packages;
};

void importDatabase(sqlite3 *db, const std::filesystem::path &dbDir, std::function<void(const std::string &file, const char *error)> callback);

/* Query DB */
std::string findDatasheetByModel(sqlite3 *db, const std::string model);

std::vector<std::string> listDatasheets(sqlite3 *db, const std::string firstChars);
std::vector<std::string> listModels(sqlite3 *db, const std::string firstChars);

DatabaseTotals countTotals(sqlite3 *db);

}}}
#endif // DATABASE_HPP
