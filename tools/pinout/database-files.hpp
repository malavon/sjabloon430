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
void exportOrderablesWithoutPinout(sqlite3 *db);
void exportPinoutData(sqlite3 *db, const string &datasheetId);
void exportSignals(sqlite3 *db);
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}} // namespace sjabloon430::tools::db
#endif // SJABLOON430_TOOLS_DATABASE_FILES_HPP
