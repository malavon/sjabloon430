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
	enum class Format { CALCULATE /* max widths from data */, FIXED /* user-specified */ };

	bool appendFile = false;
	Tx tx = Tx::BOTH;
	SQL sql = SQL::INSERT;
	Format fmt = Format::FIXED; // harmless default: use colwidth (which is empty by default)
	std::vector<int> colWidths = {};

	ExportConfig appendOverride(bool app) {
		ExportConfig res(*this);
		res.appendFile = app;
		return res;
	}

	ExportConfig fmtOverride(Format ovr) {
		ExportConfig res(*this);
		res.fmt = ovr;
		return res;
	}

	ExportConfig sqlOverride(SQL ovr) {
		ExportConfig res(*this);
		res.sql = ovr;
		return res;
	}

	ExportConfig txOverride(Tx ovr) {
		ExportConfig res(*this);
		res.tx = ovr;
		return res;
	}
};
// only publicly-accessible functions are declared here; privately used ones are in the .cpp file

void exportSignals(sqlite3 *db);
void importDatabase(sqlite3 *db, std::function<void(const std::string &file, const char *error)> callback);

}}} // namespace sjabloon430::tools::db
#endif // SJABLOON430_TOOLS_DATABASE_FILES_HPP
