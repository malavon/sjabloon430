#ifndef SJABLOON430_TOOLS_PINOUT_UI_HPP
#define SJABLOON430_TOOLS_PINOUT_UI_HPP

#include <set>
#include <unordered_map>

#include "database.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

class Configset {
  public:
	Configset() { }
	Configset(const vector<db::Orderable> &vod) : odbls(vod) { }
	// looks like an odd copy constructor, let's call it a base-it-on constructor: copy everything except given
	Configset(const Configset &cs, const vector<db::Orderable> &vod) : odbls(vod), pinsetIds(cs.pinsetIds) { }

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

	vector<db::Orderable> &orderables() {
		return odbls;
	}

	const vector<db::Orderable> &orderablesView() const {
		return odbls;
	}

	void add(db::Orderable &o) {
		add(o, o.pinset.id);
	}

	void add(db::Orderable &o, int pinsetId) {
		odbls.push_back(o);
		pinsetIdFor(o.pkg, pinsetId);
	}

	bool contains(const db::Orderable &o) const {
		for ( const db::Orderable &op : odbls ) {
			if ( op == o ) {
				return true;
			}
		}
		return false;
	}

	bool contains(const vector<db::Orderable> &vo) const {
		bool hasAll = true;
		for ( vector<db::Orderable>::const_iterator reqr = vo.cbegin(); hasAll && reqr != vo.end(); reqr++ ) {
			hasAll = contains(*reqr);
		}
		return hasAll;
	}

	bool empty() const {
		return odbls.empty();
	}

	void update(db::Orderable &o) {
		if ( o.pinset.id == 0 ) {
			o.pinset.id = pinsetIdFor(o.pkg);
		} else {
			pinsetIdFor(o.pkg, o.pinset.id);
		}
		for ( auto it = odbls.begin(); it != odbls.end(); it++ ) {
			if ( o.name == (*it).name ) {
				*it = o;
				return;
			}
		}
	}

	int pinsetIdFor(const Package &pkg) const {
		return pinsetIds.find(pkg) == pinsetIds.end() ? 0 : pinsetIds.at(pkg);
	}

  private:
	void pinsetIdFor(const Package &pkg, int id) {
		if ( id != 0 ) {
			assert(pinsetIds.find(pkg) == pinsetIds.end() || pinsetIds[pkg] == id);
			pinsetIds[pkg] = id;
		}
	}

  private:
	vector<db::Orderable> odbls;
	// configset requires pinset ids to ensure correct re-creation of all database objects
	// cache pinset ids for each configset, no matter what orderables are linked and should be linked
	unordered_map<Package, int> pinsetIds;
};

struct PinView {
	// this struct was conceived to prevent using a db:: scoped object in the ui (like db::Signalset)
	// and once parenting/configsets has been implemented it will be much more useful
	// hindsight(c) powered by rebase (R)
	struct ConfigView {
		int signalsetId = 0;
		// parentsetId = 0; // not sure if needed, don't use unless proven useful
		// indexed! 0 = (pin) default, does NOT contain empty strings
		unordered_map<unsigned int, string> signals;
	};
	vector<ConfigView> cviews; // empty by default, needs to be inserted!
	// one pin per package
	unordered_map<Package, Pin> pins;
	// experiment: getting/setting signals can happen through the [] operator to get to
	// the one and only configview (in the future, multiple signalsets will be required)
	// then again, will NOT break compilation once it is no longer a single one ...
	unordered_map<unsigned int, string> &operator[](unsigned int idx) {
		return cviews.at(idx).signals;
	}
	const unordered_map<unsigned int, string> &operator[](unsigned int idx) const {
		return cviews.at(idx).signals;
	}
	void clearSignals() {
		for ( ConfigView &cf : cviews ) {
			cf.signals.clear();
		}
	}
	int countSignals() const {
		int c = 0;
		for ( const ConfigView &cf : cviews ) {
			c += cf.signals.size();
		}
		return c;
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
		return hasPins() && countSignals() > 0;
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
	vector<Configset> csets;
	void add(Configset &cs) {
		csets.push_back(cs);
		for ( PinView &pv : pinViews ) {
			pv.cviews.push_back(PinView::ConfigView());
		}
	}
	PinView createNewPinView() {
		PinView pv;
		for ( size_t i = csets.size(); i > 0; i-- ) {
			pv.cviews.push_back(PinView::ConfigView());
		}
		return pv;
	}
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
void drawSetConfigWindow(BorderedWindow &, const vector<Configset> &cfs);
void drawTopWindow(BorderedWindow &, const db::Datasheet &, const db::DatabaseTotals &ttl, const db::DatabaseTotals &sprtd);
Configset filterForConfigset(const vector<db::Orderable> &, const Configset &base = Configset{});
void loopPinsetEditing(Window &pinset, Window &hotkeys, BorderedWindow &config, ui::PinSetView &);
void reorderPackages(vector<Package> &pkgs); // given vector is reordered in-place
string searchDatasheet(const unordered_map<string, string> &dsModels, const int modelFieldWidth);
}}}} // namespace sjabloon430::tools::pinout::ui
#endif // SJABLOON430_TOOLS_PINOUT_UI_HPP
