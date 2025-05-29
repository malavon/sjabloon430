
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

void addPinsetsToOrderables(sqlite3 *, const vector<db::Signalset> &, vector<db::Orderable> &);
void convertDbToView(const vector<db::Orderable> &, const vector<db::Signalset> &, ui::PinSetView &);
void convertViewToDb(const ui::PinSetView &vw, vector<db::Signalset> &signalsets);
void printShortcuts(Window &win);

static const int WIDEST_MODEL_LENGTH = strlen("MSP430F6459-HIREL"); /* hardcoded longest model */
static const int WIN_TOP_HEIGHT = 5;
static const int WIN_CONFIGSET_WIDTH = WIDEST_MODEL_LENGTH + 2 /* indent */ + 2 /* borders */;

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
		Window pins(LINES - WIN_TOP_HEIGHT, COLS - WIN_CONFIGSET_WIDTH, WIN_TOP_HEIGHT, 0);
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

		printShortcuts(pins);

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

		BorderedWindow newSet(6, WIN_CONFIGSET_WIDTH, defaultSetHeight, COLS - WIN_CONFIGSET_WIDTH);
		newSet.setTitle("Set F5");
		// newSet.add(0, 1, "F5: Create new set");
		/* clang-format off */ // does not format, TODO
		ui::drawSetConfigWindow(newSet, {"MOCKUP"}, {Package{"MOCKUP", 22}});
		/* clang-format on */

		// TODO: get pins from DB
		// orderables are used to create config sets (the thing at the right :p) -> but not yet implemented
		vector<db::Orderable> ordbls = db::findOrderablesByDatasheet(db, selectedId);
		// /signalsets/pinsets are also linked to orderables and thus model/package
		vector<db::Signalset> signalsets = db::findSignalsetsByDatasheet(db, selectedId);

		// does not yet use config sets, but this is where the logic could go
		addPinsetsToOrderables(db, signalsets, ordbls);

		ui::reorderPackages(pkgs);
		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(ordbls, signalsets, vw);

		ui::loopPinsetEditing(pins, vw);

		db::saveSignals(db, vw.signalDescs);
		dbf::exportSignals(db);

		convertViewToDb(vw, signalsets);
		db::saveOrUpdateSignalsets(db, signalsets);

		addPinsetsToOrderables(db, signalsets, ordbls);
		db::linkOrderableToPinset(db, ordbls);

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

void addPinsetsToOrderables(sqlite3 *db, const vector<db::Signalset> &ssets, vector<db::Orderable> &odbls) {
	vector<db::Pinset> psets;
	// config sets are not yet implemented, but right now it seems logical to me that they would be
	// a list of orderables
	// calling this function once for each config set with a different list of odbls may be correct
	unordered_map<Package, int> pkgToPinset;

	for ( db::Orderable &o : odbls ) {
		// if the pinset has not been saved yet, it is not in the pkgToPinset map
		// and thus needs to be saved in order to reflect signalset updates for that PACKAGE
		// subsequent uses do not need to be saved, and if pinset is not retrieved from database
		// doing so will clear & OVERWRITE signalsets each time
		if ( pkgToPinset[o.pkg] == 0 ) {
			// pinset doesn't have to come from database, YET because there are no config sets
			// but if orderable has a pinset linked to it, it is assumed to exist and should be updated
			db::Pinset p;
			p.id = o.pinsetId;
			p.totalPins = 0; // calculated again below

			for ( const db::Signalset &s : ssets ) {
				// always add signalset for correct index, but do not count it if empty!
				if ( s.pins.find(o.pkg) != s.pins.end() ) {
					Pin pin = s.pins.at(o.pkg);
					p.totalPins++;
					// this can only store a single empty/null pin...
					// so I stopped inserting those
					p.signalsets[pin] = s;
				}
			}

			db::saveOrUpdatePinset(db, p);
			o.pinsetId = p.id;
			pkgToPinset[o.pkg] = p.id; // will overwrite should be the same anyway
		} else {
			if ( o.pinsetId == 0 ) { // reuse pinsets for default config set if not yet linked
				o.pinsetId = pkgToPinset[o.pkg];
			}
		}
	}
}

void convertDbToView(const vector<db::Orderable> & /*ordbls*/, const vector<db::Signalset> &signalsets, ui::PinSetView &vw) {
	// orderables should be used in DB query? part of config set?
	for ( const db::Signalset &ss : signalsets ) {
		ui::PinView pv;
		pv.cview.signalsetId = ss.id;
		pv.cview.signals = ss.signals;
		pv.pins = ss.pins;
		vw.pinViews.push_back(pv);
	}
}

void convertViewToDb(const ui::PinSetView &vw, vector<db::Signalset> &signalsets) {
	signalsets.clear();

	for ( const ui::PinView &pv : vw.pinViews ) {
		db::Signalset s;
		s.id = pv.cview.signalsetId;
		s.signals = pv.cview.signals;
		s.pins = pv.pins;
		signalsets.push_back(s);
	}
}

void printShortcuts(Window &win) {
	const int LINE = 0;

	win.moveCursor(LINE, 0);
	ui::displayHotkey(win, "QUIT", "ESC");
	ui::displayHotkey(win, "Help", "F1");
	ui::displayHotkey(win, "Search", "F2");
	ui::displayHotkey(win, "Up/Down", "PgUp/PgDn");
	ui::displayHotkey(win, "Edit mode", "Ctrl+e");
	ui::displayHotkey(win, "Save", "Ctrl+s");
	ui::displayHotkey(win, "Set #", "F5-F9");
}
