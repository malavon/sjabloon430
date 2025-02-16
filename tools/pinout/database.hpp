#ifndef SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
#define SJABLOON430_TOOLS_PINOUT_DATABASE_HPP

#include <sqlite3.h>

namespace sjabloon430 { namespace tools { namespace pinout { namespace db {

/* SQLite 3 init & database import/export */
sqlite3 *createDatabase();

}}}} // namespace sjabloon430::tools::pinout::db
#endif // SJABLOON430_TOOLS_PINOUT_DATABASE_HPP
