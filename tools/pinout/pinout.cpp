#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include "database-files.hpp"
#include "database.hpp"
#include "ui.hpp"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace sjabloon430::tools;
using namespace sjabloon430::tools::pinout;

void addPinsetsToOrderables(sqlite3 *, const vector<db::Signalset> &, vector<db::Orderable> &);
void convertDbToView(const vector<db::Orderable> &, const vector<db::Signalset> &, ui::PinSetView &);
void convertViewToDb(const ui::PinSetView &, vector<db::Signalset> &);

void displayBrowseHotkeys(Window &win);
void displayEditHotkeys(Window &win);

static const string WIDEST("MSP430F6459-HIREL");

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

	static const int MODEL_INDENT = 2;
	// base on select max(length(name)) + MODEL_INDENT + 2 from device?
	static const int MAX_WIDTH = WIDEST.length() + MODEL_INDENT + 2 /*border*/;

	{
		BorderedWindow top(5, COLS - MAX_WIDTH, 0, 0);
		// TODO: no border, separate with hline or something?
		Window hotkeys(1, COLS - MAX_WIDTH, 5, 0);
		Window pins(LINES - 6, COLS - MAX_WIDTH, 6, 0);
		pins.optionScrollable(Toggle::ON);

		Window &statusWin = pins;
		statusWin.add(0, 0, "Imported SQLite DB from files:\n");
		db::importDatabase(db, [&](const string &filename, const char *error) {
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
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST.length());
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);

		db::DatabaseTotals totals = db::countTotals(db);
		db::DatabaseTotals supported = db::countSupported(db);

		ui::drawTopWindow(top, selectedDS, totals, supported);

		vector<string> models = db::findModelsByDatasheet(db, selectedId);
		// models are used for (default) set
		// TODO: other sets have to be retrieved from pinset & calculated

		vector<Package> pkgs = db::findPackagesByDatasheet(db, selectedDS.id);
		// packages are also used for sets

		ui::reorderPackages(pkgs);

		int defaultSetHeight = models.size()   /* one line per model */
				     + pkgs.size() / 2 /* packages are max 5 wide, 2 pkgs/line */
				     + pkgs.size() % 2 /* when odd, 1 extra pkg, 1 extra line */
				     + 2 /* headers */ + 2 /* borders */;
		BorderedWindow defaultSet(defaultSetHeight, MAX_WIDTH, 0, COLS - MAX_WIDTH);
		defaultSet.setTitle("Default");
		ui::drawSetConfigWindow(defaultSet, models, pkgs);

		BorderedWindow newSet(6, MAX_WIDTH, defaultSetHeight, COLS - MAX_WIDTH);
		newSet.setTitle("Set F5");
		// newSet.add(0, 1, "F5: Create new set");
		/* clang-format off */ // does not format, TODO
		ui::drawSetConfigWindow(newSet, {"MOCKUP"}, {Package{"MOCKUP", 22}});
		/* clang-format on */

		// orderables are used to create config sets (the thing at the right :p) -> but not yet implemented
		vector<db::Orderable> ordbls = db::findOrderablesByDatasheet(db, selectedId);
		// /signalsets/pinsets are also linked to orderables and thus model/package
		vector<db::Signalset> signalsets = db::findSignalsetsByDatasheet(db, selectedId);

		// does not yet use config sets, but this is where the logic could go
		addPinsetsToOrderables(db, signalsets, ordbls);

		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(ordbls, signalsets, vw);

		int tempChar = 0;
		do {
			switch ( tempChar ) {
				case KEY_UP:
					vw.selIdx = max(0, vw.selIdx - 1);
					break;
				case KEY_DOWN:
					// size() is 1 higher than max to allow selecting pin at the end
					vw.selIdx = min(static_cast<int>(vw.pinViews.size()), vw.selIdx + 1);
					break;
				case KEY_ENTER:
				case 10 /* RETURN */:
					vw.editIdx = vw.selIdx;
					displayEditHotkeys(hotkeys);
					break;
				case KEY_IC /* insert */:
					// insert and edit; will be removed by ui code if no signals are inserted!
					if ( vw.selIdx < vw.pinViews.size() ) {
						vw.pinViews.insert(vw.pinViews.begin() + vw.selIdx, ui::PinView());
						vw.editIdx = vw.selIdx;
					}
					break;
				case KEY_DC /* delete */:
					if ( vw.selIdx < vw.pinViews.size() ) {
						vw.pinViews.erase(vw.pinViews.begin() + vw.selIdx);
					}
					break;
				case 27 /*ESCAPE*/: // open a menu or something, probably beyond MVP though
					break;
			}

			ui::drawPinSetEditingWindow(pins, vw);
			displayBrowseHotkeys(hotkeys); // default hotkeys
			vw.editIdx = -1;	       // reset editIdx otherwise editing would never stop
		} while ( (tempChar = wgetch(pins)) != 27 ); // ESC key for exit

		db::saveSignals(db, vw.signalDescs);
		db::exportSignals(db);

		convertViewToDb(vw, signalsets);
		db::saveOrUpdateSignalsets(db, signalsets);

		addPinsetsToOrderables(db, signalsets, ordbls);
		db::linkOrderableToPinset(db, ordbls);

		db::exportPinoutData(db, selectedId);
		// it would make sense that these are removed and all dev's and odbls are in files per datasheet ...
		db::exportDevicesWithoutPinout(db);
		db::exportOrderablesWithoutPinout(db);

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

void convertDbToView(const vector<db::Orderable> &ordbls, const vector<db::Signalset> &signalsets, ui::PinSetView &vw) {
	// orderables should be used in DB query? part of config set?
	for ( const db::Signalset &ss : signalsets ) {
		ui::PinView pv;
		pv.signalset = ss;
		pv.pins = ss.pins; // TODO: didn't belong in signalset at all
		vw.pinViews.push_back(pv);
	}
}

void convertViewToDb(const ui::PinSetView &vw, vector<db::Signalset> &signalsets) {
	signalsets.clear();

	for ( const ui::PinView &pv : vw.pinViews ) {
		signalsets.push_back(pv.signalset);
	}
}

void displayHotkey(Window &win, const string &text, const vector<chtype> &keys) {
	win.add(' ');
	for ( const chtype key : keys ) {
		win.add(key | A_STANDOUT);
	}
	win.add(' ');
	win.add(text);
}

void displayHotkey(Window &win, const string &text, const string &key) {
	win.add(' ');
	win.add(key, A_STANDOUT);
	win.add(' ');
	win.add(text);
}

void displayBrowseHotkeys(Window &win) {
	win.moveCursor(0, 0);
	win.clearToEndOfLine();
	displayHotkey(win, "QUIT", "ESC");
	displayHotkey(win, "Nav.", vector<chtype>({ACS_UARROW, '/', ACS_DARROW}));
	displayHotkey(win, "Edit", "Enter");
	displayHotkey(win, "Insert", "Ins");
	displayHotkey(win, "Delete", "Del");
	win.paint();
}

void displayEditHotkeys(Window &win) {
	win.moveCursor(0, 0);
	win.clearToEndOfLine();
	displayHotkey(win, "Nav.", "TAB/STAB");
	displayHotkey(win, "Confirm", "Enter");
	win.paint();
}
