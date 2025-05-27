
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

void convertDbToView(const vector<db::Orderable> &, const vector<db::Signalset> &, ui::PinSetView &);
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

		int l = 20;
		Window &statusWin = pins;
		statusWin.add(l++, 0, "Imported SQLite DB from files:");
		dbf::importDatabase(db, [&](const string &filename, const char *error) {
			statusWin.add(l++, 2, '"');
			statusWin.add(filename);
			statusWin.add('"');

			if ( error != nullptr ) {
				statusWin.add(' ');
				statusWin.add(error);
			}
		});
		db::DatabaseTotals totals = db::countTotals(db);
		statusWin.paint();

		// initial state: open search window
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST_MODEL_LENGTH);
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);
		ui::drawTopWindow(top, selectedDS, totals);

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

		ui::reorderPackages(pkgs);
		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(ordbls, signalsets, vw);

		int tempChar = 0;
		do {
			ui::drawPinSetEditingWindow(pins, vw);
		} while ( (tempChar = wgetch(pins)) != 27 ); // ESC key for exit

		db::saveSignals(db, vw.signalDescs);
		dbf::exportSignals(db);

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
		pv.cview.signalsetId = ss.id;
		pv.cview.signals = ss.signals;
		pv.pins = ss.pins;
		vw.pinViews.push_back(pv);
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
