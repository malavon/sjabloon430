#ifndef UI_HPP
#define UI_HPP

#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::pinout::db;

// 3 characters is enough for pin numbers, even BGA
// using 4 is however logical, esthetic purposes 1 empty character always
static const int FIELD_WIDTH_PIN = 4;
// signal is max ... TODO=
static const int FIELD_WIDTH_SIGNAL = 8;
static const int FIELD_WIDTH_DESC = 20;
// packages (drawing + pins) are up to 6 wide, so always format them at 6
static const int HEADER_WIDTH_PKG = 6;

// hard-coded max # of signals required for window size
static const int MAX_SIGNALS = 10;

static const char *SIGNAL_HDR("SIGNAL");
static const char *DESCRIPTION_HDR("DESCRIPTION");

struct PinView {
	// one pin per package
	unordered_map<Package, string> pins;
	// multiple signals are common; indexed! begin/first = default
	vector<string> signals;
};

struct PinSetView {
	// fixed list of packages
	const vector<Package> pkgs;
	// map of all existing signals & descriptions, can be modified (well, extended at least)!
	unordered_map<string, string> signalDescs;
	// each item on the screen
	vector<PinView> pinViews;
	/*
	 * index of pin that is edited
	 * if higher than pins.size(), add at end
	 * if -1, either same or indicate that all pins are view only
	 */
	int editIdx = -1;
};

// partial drawing functions
// TODO: window should scroll working
void drawPinSetHeader(Window &, const int row, const vector<string> &pkgs);
void drawPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, const PinView &pv);
void editPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, PinView &pv);

// Window drawing functions
void drawPinSetEditingWindow(Window &win, PinSetView &pinView);
void drawSetConfigWindow(BorderedWindow &, const vector<string> &models, const vector<Package> &packages);
void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
void reorderPackages(vector<Package> &pkgs); // given vector is reordered in-place
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // UI_HPP
