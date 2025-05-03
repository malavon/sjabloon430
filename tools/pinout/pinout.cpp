#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include "database.hpp"
#include "ui.hpp"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace sjabloon430::tools::db;
using namespace sjabloon430::tools::pinout::ui;

void autofillDatasheet();
void printShortcuts(Window &win);

static const string WIDEST("MSP430F6459-HIREL");

int main() {
	setlocale(LC_ALL, "");

	// SQLite3 in-memory DB
	sqlite3 *db;
	// const char *database = "sjabloon430.db";
	// in-memory is preferred, but exporting should be simple, formatted and not DIY
	// if not, use a file database?
	unsigned int rc = sqlite3_open("file::memory:", &db);
	std::filesystem::path dbDir(DB_DIRECTORY);

	if ( rc != 0 ) {
		sqlite3_close(db);
		return 1;
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

		int l = 20;
		Window &statusWin = pins;
		statusWin.add(l++, 0, "Imported SQLite DB from files:");
		importDatabase(db, dbDir, [&](const string &filename, const char *error) {
			statusWin.add(l++, 2, '"');
			statusWin.add(filename);
			statusWin.add('"');

			if ( error != nullptr ) {
				statusWin.add(' ');
				statusWin.add(error);
			}
		});
		DatabaseTotals totals = countTotals(db);
		statusWin.paint();

		// initial state: open search window
		string selectedId = searchDatasheet(listAllModelsAndDatasheets(db), WIDEST.length());
		Datasheet selectedDS = findDatasheet(db, selectedId);
		drawTopWindow(top, selectedDS, totals);

		printShortcuts(pins);

		vector<string> models = findModelsByDatasheet(db, selectedId);
		// models are used for (default) set
		// TODO: other sets have to be retrieved from pinset & calculated

		vector<string> pkgs = findPackagesByDatasheet(db, selectedDS.id);
		// packages are also used for sets

		int defaultSetHeight = models.size() + pkgs.size() / 2 /* packages are max 5 wide */ + pkgs.size() % 2 /* when odd, add 1 */
							 + 2 /* headers */ + 2 /* borders */;
		BorderedWindow defaultSet(defaultSetHeight, MAX_WIDTH, 0, COLS - MAX_WIDTH);
		defaultSet.setTitle("Default");
		drawSetConfigWindow(defaultSet, models, pkgs);

		BorderedWindow newSet(6, MAX_WIDTH, defaultSetHeight, COLS - MAX_WIDTH);
		newSet.setTitle("Set F5");
		// newSet.add(0, 1, "F5: Create new set");
		drawSetConfigWindow(newSet, {"MOCKUP"}, {"MOCKUP"});

		// TODO: really should be possible to re-order packages and possibly other things!
		// other centered screen to quickly do this?
		// idea: quick-n-dirt: input field with number, default numbers start from # pkgs+1 (not shown in fields though)
		// i.e. 4 packages DA, N, RHB, YXW: "weight" 5,6,7,8; putting # in any field makes easy first/second etc?
		// set N to 1, becomes N, DA, RHB, YXW; but what happens when setting to 2 instead of 1? NOT AS EXPECTED becomes first
		// maybe just default indices and when filled, swap? dunno, also error-prone
		PinSetView vw = {pkgs};
		// TODO: just a test signal
		vw.signalDescs["TEST"] = "TEST SIGNAL DESC";
		// TODO: get pins & signals from DB

		PinView pv;
		int tempChar = 0;
		do {
			drawPinSetEditingWindow(pins, vw);
		} while ( (tempChar = wgetch(pins.raw())) != 27 ); // ESC key for exit

		// TODO: input up/down & other hotkeys, basically the bulk of the application?
		// or should this be in the main application?
		// much more logical I think, since DB access is required for saving

		// TODO: save new signals; allow changes to descs? maybe, maybe not? better manually?

		// next step would be: get pinset, render to screen
		// BUT: there are no pinsets in DB yet, so first thing is to add creation/editing code
		/* MVP sequence:
		 * 1. get packages & pins for datasheet, get models (models from vector? more difficult)
		 * 2. print header (assume all packages are added in one go, type 1 datasheets)
		 * 3. add form for pins under each package + 1 signal, on signal field 1 tab:
		 * 3a. lookup signal (none in DB yet), show description
		 * 3b. if description empty: add REQUIRED field // TODO: form extension? unpost/post? tab focuses
		 * 3c. tab: create new signal field
		 * 3d. tab: if next signal field filled, go to 3b, otherwise 4
		 * 4. add new pin, go to 3 (or 2? maybe every X pins?)
		 */
		/* MVP+1:
		 * adds package ordering? on hotkey? on menu item? not sure -> almost REQUIRED for ease of use ... + correctness
		 * uppercase input only?
		 * V1.0
		 * autocomplete signals from DB
		 */
	}

	endCurses();

	return EXIT_SUCCESS;
}

// this function assumes the screen is on the defaultSet position to make it simpler
void printShortcut(Window &window, const string &key, const string &text) {
	window.add(' ');
	window.add(key, A_STANDOUT);
	window.add(' ');
	window.add(text);
}

// print shortcuts to wrapper now
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
