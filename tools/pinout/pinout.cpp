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

void convertDbToView(const vector<db::Orderable> &, const vector<db::Signalset> &, ui::PinSetView &);
void convertViewToDb(const ui::PinSetView &, vector<db::Signalset> &);
void printShortcuts(Window &win);

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

		printShortcuts(pins);

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

		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(ordbls, signalsets, vw);

		int tempChar = 0;
		do {
			ui::drawPinSetEditingWindow(pins, vw);
		} while ( (tempChar = wgetch(pins)) != 27 ); // ESC key for exit

		db::saveSignals(db, vw.signalDescs);
		db::exportSignals(db);

		convertViewToDb(vw, signalsets);
		db::saveSignalsets(db, signalsets);

		db::exportPinoutData(db, selectedId);
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

void convertDbToView(const vector<db::Orderable> &ordbls, const vector<db::Signalset> &signalsets, ui::PinSetView &vw) {
	// orderables should be used in DB query? part of config set?
	for ( const db::Signalset &ss : signalsets ) {
		ui::PinView pv;
		pv.signalset = ss;
		pv.pins = ss.pins;
		vw.pinViews.push_back(pv);
	}
}
void convertViewToDb(const ui::PinSetView &vw, vector<db::Signalset> &signalsets) {
	signalsets.clear();

	for ( const ui::PinView &pv : vw.pinViews ) {
		signalsets.push_back(pv.signalset);
	}
}

// this function assumes the screen is on the defaultSet position to make it simpler
void printShortcut(Window &window, const string &key, const string &text) {
	window.add(' ');
	window.add(key, A_STANDOUT);
	window.add(' ');
	window.add(text);
}

void printShortcuts(Window &hotkeyWin) {
	const int LINE = 0;

	hotkeyWin.moveCursor(LINE, 0);
	printShortcut(hotkeyWin, "ESC", "QUIT");
	printShortcut(hotkeyWin, "F1", "Help");
	printShortcut(hotkeyWin, "F2", "Search");
	printShortcut(hotkeyWin, "PgUp/PgDn", "Up/Down");
	printShortcut(hotkeyWin, "Ctrl+e", "Edit Mode");
	printShortcut(hotkeyWin, "Ctrl+s", "Save");
	printShortcut(hotkeyWin, "F5-F9", "Set #");
}
