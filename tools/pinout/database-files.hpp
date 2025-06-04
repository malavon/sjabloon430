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
	std::vector<int> colWidths;
};

// only publicly-accessible functions are declared here; privately used ones are in the .cpp file

void exportSignals(sqlite3 *db);
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}}
#endif // SJABLOON430_TOOLS_DATABASE_FILES_HPP
