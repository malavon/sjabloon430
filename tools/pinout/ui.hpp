#ifndef SJABLOON430_TOOLS_PINOUT_UI_HPP
#define SJABLOON430_TOOLS_PINOUT_UI_HPP

#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

struct PinView {
	// this struct was conceived to prevent using a db:: scoped object in the ui (like db::Signalset)
	// and once parenting/configsets has been implemented it will be much more useful
	// hindsight(c) powered by rebase (R)
	struct ConfigView {
		int signalsetId = 0;
		// parentsetId = 0; // not sure if needed, don't use unless proven useful
		// indexed! first = (pin) default
		vector<string> signals;
	};
	ConfigView cview;
	// one pin per package
	unordered_map<Package, Pin> pins;
	// experiment: getting/setting signals can happen through the [] operator to get to
	// the one and only configview (in the future, multiple signalsets will be required)
	// then again, will NOT break compilation once it is no longer a single one ...
	vector<string> &operator[](int idx) {
		assert(idx == 0);
		return cview.signals;
	}
	const vector<string> &operator[](int idx) const {
		assert(idx == 0);
		return cview.signals;
	}
	bool hasPins() const {
		for ( const std::pair<const Package, Pin> &pr : pins ) {
			if ( !pr.second.empty() ) {
				return true;
			}
		}
		return false;
	}
	bool hasPinsAndSignals() const {
		return hasPins() && !cview.signals.empty();
	}
};

struct PinSetView {
	PinSetView(const vector<Package> p) : pkgs(p) { }
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
	unsigned int selIdx = 0;
};

// partial drawing functions
// TODO: window should scroll working
void drawPinSetHeader(Window &, const int row, const vector<string> &pkgs);
void drawPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, const PinView &pv);
void editPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, PinView &pv);

// Window drawing functions
void drawPinSetEditingWindow(Window &win, PinSetView &pinView);
void drawSetConfigWindow(BorderedWindow &, const vector<db::Orderable> odbls);
void drawSetConfigWindow(BorderedWindow &, const vector<string> &models, const vector<Package> &packages);
void drawTopWindow(BorderedWindow &, const db::Datasheet &, const db::DatabaseTotals &ttl, const db::DatabaseTotals &sprtd);
vector<db::Orderable> filterForConfigset(const vector<Package> &, const vector<string> &ms, const vector<db::Orderable> &);
void loopPinsetEditing(Window &pinset, Window &hotkeys, BorderedWindow &config, ui::PinSetView &,
		       vector<db::Orderable> &ordbls);
void reorderPackages(vector<Package> &pkgs); // given vector is reordered in-place
string searchDatasheet(const unordered_map<string, string> &dsModels, const int modelFieldWidth);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // SJABLOON430_TOOLS_PINOUT_UI_HPP
