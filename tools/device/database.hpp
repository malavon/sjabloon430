#ifndef SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
#define SJABLOON430_TOOLS_DEVICE_DATABASE_HPP

#include <string>

#include "sqlite3.h"

namespace sjabloon430 { namespace tools { namespace device { namespace db {

using std::string;

/* Simple data objects, no need for encapsulation in a privately used tool ... */
struct Datasheet {
	struct Date {
		// these are strings because FOR THIS PROGRAM it doesn't matter
		// the database knows the correct type and will return error(s) when incorrect!
		int month, year;
	};
	string id;
	string rev;
	Date issued;
	Date revised;
};

/* SQLite 3 init */
sqlite3 *createDatabase();

/* Data modifications */
int saveOrUpdate(sqlite3 *, const Datasheet &ds);

}}}} // namespace sjabloon430::tools::device::db
#endif // SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
