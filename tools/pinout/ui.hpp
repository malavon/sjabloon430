#ifndef UI_HPP
#define UI_HPP

#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::db;

void drawPin(Window &win, const vector<string> &pkgs);
void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength);

}}}}
#endif // UI_HPP
