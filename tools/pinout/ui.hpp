#ifndef UI_HPP
#define UI_HPP

#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::db;

// 3 characters is enough for pin numbers, even BGA
// using 4 is however logical, esthetic purposes 1 empty character always
static const int PIN_FIELD_WIDTH = 4;
// packages (drawing + pins) are up to 6 wide, so always format them at 6
static const int PKG_HDR_WIDTH = 6;
// signal is max ... TODO=
static const int FIELD_WIDTH_SIGNAL = 8;
static const int FIELD_WIDTH_DESC = 20;

static const char *SIGNAL_HDR("SIGNAL");
static const char *DESCRIPTION_HDR("DESCRIPTION");

struct PinView {
	// one pin per package
	vector<string> pins;
	// multiple signals are common; indexed! begin/first = default
	vector<string> signals;
};

struct PinSetView {
	// fixed list of packages
	const vector<string> pkgs;
	// semi-fixed list of all existing signals
	// new signals can be added
	// TODO: set that doesn't allow deletion better? also vector not really best?
	// maybe better map type?
	vector<struct SignalView> signals;
	// each item on the screen
	vector<PinView> pins;
	/*
	 * index of pin that is edited
	 * if higher than pins.size(), add at end
	 * if -1, either same or indicate that all pins are view only
	 */
	int editIdx = -1;
};

struct SignalView {
	string signal;
	string desc;
};

// partial drawing functions
// TODO: window should scroll working
void drawPinSetHeader(Window &, const int row, const vector<string> &pkgs);
void drawPinSet(Window &, int row, const vector<string> &pkgs, PinView &pv);
void editPinSet(Window &, int row, const vector<string> &pkgs, PinView &pv);

// Window drawing functions
void drawPinSetEditingWindow(Window &win, PinSetView &pinView);
void drawSetConfigWindow(BorderedWindow &, const vector<string> &models, const vector<string> &packages);
void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // UI_HPP
