#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>

namespace sjabloon430 { namespace tools { namespace db {

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}} // namespace sjabloon430::tools::db
#endif // DATABASE_HPP
