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
void drawSetConfigWindow(BorderedWindow &, const vector<string> &models, const vector<string> &packages);
void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &);
void reorderPackages(vector<string> &pkgs); // given vector is reordered in-place
string searchDatasheet(const unordered_map<string, string> &dsModels, const int modelFieldWidth);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // SJABLOON430_TOOLS_PINOUT_UI_HPP
