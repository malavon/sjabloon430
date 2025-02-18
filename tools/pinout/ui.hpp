#ifndef SJABLOON430_TOOLS_PINOUT_UI_HPP
#define SJABLOON430_TOOLS_PINOUT_UI_HPP

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::pinout::db;

void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
Datasheet searchDatasheet(sqlite3 *db, const int modelFieldWidth);

}}}}
#endif // SJABLOON430_TOOLS_PINOUT_UI_HPP
