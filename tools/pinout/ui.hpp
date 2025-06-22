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
  private:
	PinView() { } // only allow creation by 'friend' class

  public:
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

	friend class PinSetView;
};

class PinSetView {
	typedef vector<PinView>::iterator internal_iterator;

  public:
	// wrapping iterator?
	template<typename dataType>
	class OrderingIterator {
	  public:
		// OrderingIterator traits
		using difference_type = int;
		using value_type = PinView;
		using pointer = const dataType *;
		using reference = const PinView &;
		using iterator_category = std::forward_iterator_tag;
		using wrapped_iterator = vector<int>::iterator;

		OrderingIterator(vector<value_type> &val, wrapped_iterator wrp) : wrapped(wrp), original(val) { }

		OrderingIterator(const OrderingIterator<dataType> &raw) = default;

		bool operator==(const OrderingIterator<dataType> &raw) const {
			return wrapped == raw.wrapped;
		}

		bool operator!=(const OrderingIterator<dataType> &raw) const {
			return wrapped != raw.wrapped;
		}

		OrderingIterator<dataType> &operator+=(const difference_type &movement) {
			wrapped += movement;
			return *this;
		}

		OrderingIterator<dataType> &operator-=(const difference_type &movement) {
			wrapped -= movement;
			return *this;
		}

		OrderingIterator<dataType> &operator++() {
			++wrapped;
			return *this;
		}

		OrderingIterator<dataType> &operator--() {
			--wrapped;
			return *this;
		}

		OrderingIterator<dataType> operator++(int) {
			auto temp(*this);
			++wrapped;
			return temp;
		}

		OrderingIterator<dataType> operator--(int) {
			auto temp(*this);
			--wrapped;
			return temp;
		}

		OrderingIterator<dataType> operator+(const difference_type &movement) {
			wrapped_iterator oldPtr = wrapped;
			wrapped += movement;
			auto temp(*this);
			wrapped = oldPtr;
			return temp;
		}

		OrderingIterator<dataType> operator-(const difference_type &movement) {
			wrapped_iterator oldPtr = wrapped;
			wrapped -= movement;
			auto temp(*this);
			wrapped = oldPtr;
			return temp;
		}

		dataType &operator*() {
			return original[*wrapped];
		}

		const dataType &operator*() const {
			return original[*wrapped];
		}

		wrapped_iterator getWrapped() {
			return wrapped;
		}

	  private:
		wrapped_iterator wrapped;
		vector<value_type> &original;
	};

	typedef OrderingIterator<PinView> iterator;
	typedef OrderingIterator<const PinView> const_iterator;

	PinSetView(const vector<Package> &p) : pkgs(p) { }

	// factory method to create a valid PinView
	PinView createNewPinView() const {
		PinView pv;
		for ( size_t i = csets.size(); i > 0; i-- ) {
			pv.cviews.push_back(PinView::ConfigView());
		}
		return pv;
	}

	void add(Configset &cs) {
		csets.push_back(cs);
		for ( PinView &pv : pinViews ) {
			pv.cviews.push_back(PinView::ConfigView());
		}
	}

	/* vector<PinView>-like operation */
	iterator begin() {
		assert(ordIdx.size() == pinViews.size());
		return iterator(pinViews, ordIdx.begin());
	}

	const_iterator cbegin() {
		assert(ordIdx.size() == pinViews.size());
		return const_iterator(pinViews, ordIdx.begin());
	}

	const_iterator cend() {
		assert(ordIdx.size() == pinViews.size());
		return const_iterator(pinViews, ordIdx.end());
	}

	iterator end() {
		assert(ordIdx.size() == pinViews.size());
		return iterator(pinViews, ordIdx.end());
	}

	iterator erase(iterator it) {
		vector<int>::iterator wrp = it.getWrapped();
		int idx = ordIdx[*wrp];
		pinViews.erase(pinViews.begin() + idx);
		// ordIdx cannot be erased as-is, indices are changed ...
		// TODO: trigger 'reorder' instead?
		for ( int &i : ordIdx ) {
			if ( i >= idx ) {
				i--;
			}
		}
		return iterator(pinViews, ordIdx.erase(wrp));
	}

	iterator insert(iterator it, const PinView &pv) {
		// insert is undefined when ordering! asserted but view code should not allow this!
		assert(orderByPkgIdx == ORDERING_DEFAULT);
		vector<int>::iterator wrp = it.getWrapped();
		int idx = ordIdx[*wrp];
		internal_iterator pvIt = pinViews.insert(pinViews.begin() + idx, pv);
		for ( int &i : ordIdx ) {
			if ( i >= idx ) {
				i++;
			}
		}
		return iterator(pinViews, ordIdx.insert(wrp, pvIt - pinViews.begin()));
	}

	void push_back(PinView &pv) {
		int psize = pv.cviews.size(), csize = csets.size();
		// "upgrade" if need be
		for ( int i = csize - psize; i >= 0; i-- ) {
			pv.cviews.push_back(PinView::ConfigView());
		}
		// always adds to end of UNORDERED collection
		ordIdx.push_back(pinViews.size());
		pinViews.push_back(pv);
		// then reorder?
	}

	// bulk import of empty elements
	void ensureSize(int requiredSize) {
		for ( int i = pinViews.size(); i <= requiredSize; i++ ) {
			PinView pv = createNewPinView();
			push_back(pv);
		}
	}

	size_t size() {
		assert(ordIdx.size() == pinViews.size());
		return pinViews.size();
	}

	PinView &operator[](size_t idx) {
		assert(idx < ordIdx.size());
		return pinViews.at(ordIdx[idx]);
	}

	const PinView &operator[](size_t idx) const {
		assert(idx < ordIdx.size());
		return pinViews.at(ordIdx[idx]);
	}

  public:
	// fixed list of packages
	const vector<Package> pkgs;
	// map of all existing signals & descriptions, can be modified (well, extended at least)!
	unordered_map<string, string> signalDescs;
	vector<Configset> csets;

  private:
	// each item on the screen
	vector<PinView> pinViews;
	// ordering mapping: pinview cannot be re-ordered directly (for datasheet idx), but is mapped
	vector<int> ordIdx;

  public:
	static const int ORDERING_DEFAULT = -1; // default ordering as created datasheet_idx; otherwise order by package
	int orderByPkgIdx = ORDERING_DEFAULT;
	/*
	 * index of pin that is edited
	 * if higher than pins.size(), add at end
	 * if -1, either same or indicate that all pins are view only
	 */
	int editIdx = -1;
	/* selection index, for browsing; 0-based */
	size_t selIdx = 0;
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
