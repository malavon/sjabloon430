#ifndef UI_HPP
#define UI_HPP

#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

#include "database.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::db;

void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
Datasheet searchDatasheet(sqlite3 *db, const int widestModelLength);

}}}}
#endif // UI_HPP
