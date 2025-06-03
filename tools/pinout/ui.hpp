#ifndef UI_HPP
#define UI_HPP

#include <set>
#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

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

class Configset {
  public:
	Configset() { }

	Configset(const vector<db::Orderable> &vod) : odbls(vod) { }

	const vector<string> toModels() const {
		std::set<string> models;
		for ( const db::Orderable &o : odbls ) {
			models.insert(o.model);
		}
		return vector<string>(models.begin(), models.end());
	}

	const vector<Package> toPkgs() const {
		std::set<Package> pkgs;
		for ( const db::Orderable &o : odbls ) {
			pkgs.insert(o.pkg);
		}
		return vector<Package>(pkgs.begin(), pkgs.end());
	}

	const vector<db::Orderable> orderables() const {
		return odbls;
	}

	void add(db::Orderable &o) {
		odbls.push_back(o);
	}

  private:
	vector<db::Orderable> odbls;
};

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
		for ( const std::pair<Package, Pin> &pr : pins ) {
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
	// fixed list of packages
	const vector<Package> pkgs;
	// map of all existing signals & descriptions, can be modified (well, extended at least)!
	unordered_map<string, string> signalDescs;
	// each item on the screen
	vector<PinView> pinViews;
	vector<Configset> csets;
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
void drawSetConfigWindow(Window &, const Configset &cset);
void drawTopWindow(BorderedWindow &, const db::Datasheet &, const db::DatabaseTotals &ttl, const db::DatabaseTotals &sprtd);
Configset filterForConfigset(const Configset &cset);
void loopPinsetEditing(Window &pinset, Window &hotkeys, Window &config, ui::PinSetView &);
void reorderPackages(vector<Package> &pkgs); // given vector is reordered in-place
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength);

}}}} // namespace sjabloon430::tools::pinout::ui
#endif // UI_HPP
