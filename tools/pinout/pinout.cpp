
#include <iostream>
#include <set>

#include "database-files.hpp"
#include "database.hpp"
#include "ui.hpp"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace sjabloon430::tools::pinout;
namespace dbf = sjabloon430::tools::db;
using sjabloon430::tools::Package;
using sjabloon430::tools::Pin;

void addPinsetsToOrderables(sqlite3 *, vector<db::Orderable> &);
void convertDbToView(const vector<db::Orderable> &, const vector<db::Signalset> &, ui::PinSetView &);
void convertAndSaveViewToDb(const ui::PinSetView &, vector<db::Signalset> &);
void convertAndSaveViewToDb(sqlite3 *db, const ui::PinSetView &, vector<db::Orderable> &);

static const int WIDEST_MODEL_LENGTH = strlen("MSP430F6459-HIREL"); /* hardcoded longest model */

static const int WIN_TOP_HEIGHT = 6;
static const int WIN_CONFIGSET_WIDTH = WIDEST_MODEL_LENGTH + 2 /* indent */ + 2 /* borders */;

static const int ROW_HOTKEYS = WIN_TOP_HEIGHT - 2 /* borders*/ - 1 /* last line */;

int main() {
	setlocale(LC_ALL, "");

	// SQLite3 in-memory DB
	sqlite3 *db = db::createDatabase();
	if ( db == nullptr ) {
		exit(-1);
	}
	// importing database happens after curses setup, showing which files are read

	/* Initialize curses */
	initCurses();

	{
		BorderedWindow top(WIN_TOP_HEIGHT, COLS - WIN_CONFIGSET_WIDTH, 0, 0);
		// TODO: no border, separate with hline or something?
		Window hotkeys = top.deriveWindow(1, top.maxCols(), ROW_HOTKEYS, 0);
		Window pins(LINES - 6, COLS - WIN_CONFIGSET_WIDTH, 6, 0);
		pins.optionScrollable(Toggle::ON);

		Window &statusWin = pins;
		statusWin.add(0, 0, "Imported SQLite DB from files:\n");
		dbf::importDatabase(db, [&](const string &filename, const char *error) {
			statusWin.add("   \"");
			statusWin.add(filename);
			statusWin.add('"');

			if ( error != nullptr ) {
				statusWin.add(" ERR: ");
				statusWin.add(error);
			}
			statusWin.add('\n'); // scrolls if too many lines for window without possibly erroring
		});
		statusWin.paint();

		// initial state: open search window
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST_MODEL_LENGTH);
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);

		db::DatabaseTotals totals = db::countTotals(db);
		db::DatabaseTotals supported = db::countSupported(db);

		ui::drawTopWindow(top, selectedDS, totals, supported);

		vector<string> models = db::findModelsByDatasheet(db, selectedId);
		// models are used for (default) set
		// TODO: other sets have to be retrieved from pinset & calculated

		vector<Package> pkgs = db::findPackagesByDatasheet(db, selectedDS.id);
		// packages are also used for sets

		int defaultSetHeight = models.size()   /* one line per model */
				     + pkgs.size() / 2 /* packages are max 5 wide, 2 pkgs/line */
				     + pkgs.size() % 2 /* when odd, 1 extra pkg, 1 extra line */
				     + 2 /* headers */ + 2 /* borders */;
		BorderedWindow defaultSet(defaultSetHeight, WIN_CONFIGSET_WIDTH, 0, COLS - WIN_CONFIGSET_WIDTH);
		defaultSet.setTitle("Default");
		ui::drawSetConfigWindow(defaultSet, models, pkgs);

		BorderedWindow newSet(defaultSetHeight, WIN_CONFIGSET_WIDTH, defaultSetHeight, COLS - WIN_CONFIGSET_WIDTH);
		newSet.setTitle("Set F5");
		// newSet.add(0, 1, "F5: Create new set");
		/* clang-format off */ // does not format, TODO
		ui::drawSetConfigWindow(newSet, {"MOCKUP"}, {Package{"MOCKUP", 22}});
		/* clang-format on */

		// /signalsets/pinsets are also linked to orderables and thus model/package
		vector<db::Signalset> signalsets = db::findSignalsetsByDatasheet(db, selectedId);
		// does not yet use config sets, but this is where the logic could go
		vector<db::Pinset> pinsets = db::findPinsetsByDatasheet(db, selectedId, signalsets);
		// orderables are used to create config sets (the thing at the right :p) -> but not yet implemented
		vector<db::Orderable> ordbls = db::findOrderablesByDatasheet(db, selectedId, pinsets);
		addPinsetsToOrderables(db, ordbls);

		ui::reorderPackages(pkgs);
		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(ordbls, signalsets, vw);

		ui::loopPinsetEditing(pins, hotkeys, newSet, vw, ordbls);

		db::saveSignals(db, vw.signalDescs);
		dbf::exportSignals(db);

		convertAndSaveViewToDb(db, vw, ordbls);

		dbf::exportDataForDatasheet(db, selectedId);
		// it would make sense that these are removed and all dev's and odbls are in files per datasheet ...
		dbf::exportDevicesWithoutPinout(db);
		dbf::exportOrderablesWithoutPinout(db);

		// TODO: input up/down & other hotkeys, basically the bulk of the application?
		// or should this be in the main application?
		// much more logical I think, since DB access is required for saving

		// TODO: save new signals; allow changes to descs? maybe, maybe not? better manually?

		// next step would be: get pinset, render to screen
		// BUT: there are no pinsets in DB yet, so first thing is to add creation/editing code
		/* MVP sequence:
		 * 1. get packages & pins for datasheet, get models (models from vector? more difficult)
		 * 1a. user orders packages according to datasheet
		 * 2. print header (assume all packages are added in one go, type 1 datasheets)
		 * 3. add form for pins under each package + 1 signal, on signal field 1 tab:
		 * 3a. lookup signal (none in DB yet), show description
		 * 3b. if description empty: add REQUIRED field // TODO: form extension? unpost/post? tab focuses
		 * 3c. tab: create new signal field
		 * 3d. tab: if next signal field filled, go to 3b, otherwise 4
		 * 4. add new pin, go to 3 (or 2? maybe every X pins?)
		 */
		/* MVP+1:
		 * uppercase input only?
		 * V1.0
		 * autocomplete signals from DB
		 */
	}

	endCurses();

	return EXIT_SUCCESS;
}

void addPinsetsToOrderables(sqlite3 *db, vector<db::Orderable> &odbls) {
	// config sets are not yet implemented, but right now it seems logical to me that they would be
	// a list of orderables
	// calling this function once for each config set with a different list of odbls may be correct
	unordered_map<Package, int> pkgToIdx; // will make copies, not references
	vector<db::Pinset> pinsets;	      // handy to get references from

	// first iterate all and list pinsets in case a few orderables have pinsets and a few don't
	// don't rely on ordering and make sure to not create a new pinset when it's already in the db
	for ( db::Orderable &o : odbls ) {
		if ( o.pinset.id != 0 && pkgToIdx.find(o.pkg) == pkgToIdx.end() ) {
			pkgToIdx[o.pkg] = pinsets.size();
			pinsets.push_back(o.pinset);
		}
	}

	// only then link the other (may be new) orderables, if need be create a new pinset
	for ( db::Orderable &o : odbls ) {
		if ( o.pinset.id == 0 ) {
			if ( pkgToIdx.find(o.pkg) == pkgToIdx.end() ) {
				db::saveOrUpdatePinset(db, o.pinset);
				pkgToIdx[o.pkg] = pinsets.size();
				pinsets.push_back(o.pinset);
			} else {
				o.pinset = pinsets[pkgToIdx[o.pkg]];
			}
		}
	}
}

void convertDbToView(const vector<db::Orderable> &ordbls, const vector<db::Signalset> &signalsets, ui::PinSetView &vw) {
	// orderables should be used in DB query? part of config set?
	for ( const db::Signalset &ss : signalsets ) {
		ui::PinView pv;
		pv.cview.signalsetId = ss.id;
		pv.cview.signals = ss.signals;

		for ( const db::Orderable &o : ordbls ) {
			for ( const pair<Pin, db::Signalset> &pr : o.pinset.signalsets ) {
				if ( pr.second.id == ss.id ) {
					pv.pins[o.pkg] = pr.first;
					break;
				}
			}
		}
		vw.pinViews.push_back(pv);
	}
}

void convertAndSaveViewToDb(sqlite3 *db, const ui::PinSetView &vw, vector<db::Orderable> &odbls) {
	vector<db::Signalset> signalsets; // kept locally only?

	// reset pinset total counts, needs to be recalculated after edit
	// note that pinsets are supposed to all have a valid id already in this function
	for ( db::Orderable &o : odbls ) {
		o.pinset.pins = 0;
	}

	for ( const ui::PinView &pv : vw.pinViews ) {
		db::Signalset s;
		s.id = pv.cview.signalsetId;
		s.signals = pv.cview.signals;
		signalsets.push_back(s);
	}
	// save to database to ensure ids are valid
	db::saveOrUpdateSignalsets(db, signalsets);

	int idx = 0;
	for ( const db::Signalset &ss : signalsets ) {
		// using the fact that PinView has same index as Signalset!
		ui::PinView pv = vw.pinViews[idx++];
		for ( const pair<Package, Pin> &pr : pv.pins ) {
			for ( db::Orderable &o : odbls ) {
				if ( o.pkg == pr.first && !pr.second.empty() ) {
					o.pinset.signalsets[pr.second] = ss;
					o.pinset.pins++;
				}
			}
		}
	}

	for ( db::Orderable &o : odbls ) {
		// TODO: are these references? if so, no need to update n times
		// if not: they should really be!!!
		db::saveOrUpdatePinset(db, o.pinset);
		db::linkOrderableToItsPinset(db, o);
	}
}
