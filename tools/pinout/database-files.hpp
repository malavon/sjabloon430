#ifndef SJABLOON430_TOOLS_DATABASE_FILES_HPP
#define SJABLOON430_TOOLS_DATABASE_FILES_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>

namespace sjabloon430 { namespace tools { namespace db {

void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}}
#endif // SJABLOON430_TOOLS_DATABASE_FILES_HPP
