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
	// this struct was conceived to prevent using a db:: scoped object in the ui (like db::Signalset)
	// and once parenting/configsets has been implemented it will be much more useful
	// hindsight(c) powered by rebase (R)
	struct Link {
		int signalsetId = 0;
		// parentsetId = 0; // not sure if needed, don't use unless proven useful
		vector<string> signals;
		// indexed! first = (pin) default
		bool hasSignals() const {
			return !signals.empty();
		}
	};
	// one pin per package
	unordered_map<Package, Pin> pins;
	db::Signalset signalset;
	// Link link;
	// vector<Link> links;

	bool hasPins() const {
		for ( const std::pair<Package, Pin> &pr : pins ) {
			if ( !pr.second.empty() ) {
				return true;
			}
		}
		return false;
	}

	bool hasPinsAndSignals() const {
		return hasPins() && !signalset.signals.empty();
	}
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
	/* selection index, for browsing; 0-based */
	int selIdx = 0;
};

// partial drawing functions
// TODO: window should scroll working
void drawPinSetHeader(Window &, const int row, const vector<string> &pkgs);
void drawPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, const PinView &pv);
void editPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, PinView &pv);

// Window drawing functions
void drawPinSetEditingWindow(Window &win, PinSetView &pinView);
void drawSetConfigWindow(BorderedWindow &, const vector<string> &models, const vector<Package> &packages);
void drawTopWindow(BorderedWindow &, const Datasheet &, DatabaseTotals &totals, DatabaseTotals &supported);
void reorderPackages(vector<Package> &pkgs);
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength);

// basic browse/edit/view pin assignment functionality; bulk of what this application is intented to do

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // UI_HPP
