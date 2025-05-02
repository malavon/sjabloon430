#ifndef SJABLOON430_TOOLS_PINOUT_UI_HPP
#define SJABLOON430_TOOLS_PINOUT_UI_HPP

#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::pinout::db;

struct PinView {
	// one pin per package
	vector<string> pins;
	// multiple signals are common; indexed! begin/first = default
	vector<string> signals;
};

struct PinSetView {
	PinSetView(const vector<string> p) : pkgs(p) { }
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
string searchDatasheet(const unordered_map<string, string> &dsModels, const int modelFieldWidth);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // SJABLOON430_TOOLS_PINOUT_UI_HPP
