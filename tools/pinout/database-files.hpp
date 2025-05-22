#ifndef SJABLOON430_TOOLS_DATABASE_FILES_HPP
#define SJABLOON430_TOOLS_DATABASE_FILES_HPP

#include <sqlite3.h>

#include <filesystem>
#include <functional>
#include <string>

namespace sjabloon430 { namespace tools { namespace db {

using std::string;

// modify export behaviour
struct ExportConfig {
	enum class Tx { NONE, BEGIN, COMMIT, BOTH };
	enum class SQL { INSERT, UPDATE };

	bool appendFile = false;
	Tx tx = Tx::BOTH;
	SQL sql = SQL::INSERT;
};

// export from a simple query, cannot export joined tables etc
void exportFromPrepStmt(sqlite3_stmt *statement, const string fileName, const ExportConfig &config = ExportConfig{});
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}}
#endif // SJABLOON430_TOOLS_DATABASE_FILES_HPP
