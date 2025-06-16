#ifndef SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
#define SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
#include "sqlite3.h"

namespace sjabloon430 { namespace tools { namespace device { namespace db {

/* SQLite 3 init */
sqlite3 *createDatabase();

}}}} // namespace sjabloon430::tools::device::db
#endif // SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
