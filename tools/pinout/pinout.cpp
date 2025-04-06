
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

void printShortcuts();

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
		BorderedWindow defaultSet(10, WIN_CONFIGSET_WIDTH, 0, COLS - WIN_CONFIGSET_WIDTH);
		BorderedWindow newSet(3, WIN_CONFIGSET_WIDTH, 10, COLS - WIN_CONFIGSET_WIDTH);
		// TODO: no border, separate with hline or something?
		Window pins(LINES - WIN_TOP_HEIGHT - 1, COLS - WIN_CONFIGSET_WIDTH, WIN_TOP_HEIGHT + 1, 0);

		int lr = 0;
		defaultSet.setTitle("Default");
		defaultSet.add(lr++, 1, "Models: MOCK UP!");
		defaultSet.add(lr++, 2, "MSP430FR2532");
		defaultSet.add(lr++, 2, "MSP430FR2533");
		defaultSet.add(lr++, 2, "MSP430FR2632");
		defaultSet.add(lr++, 2, "MSP430FR2633");
		defaultSet.add(lr++, 1, "Packages:");
		defaultSet.add(lr++, 2, "RHB32, DA32,\n  RGE24, YQW24");

		newSet.setTitle("Set F5");
		newSet.add(0, 0, "F5: Create new set");

		// note: 3 characters for pin number is enough (even for BGA)
		// firstPin.add(0, 1, " RHB32   DA32  RGE24  YQW24\tSignal\t\tDescription");
		// firstPin.add(1, 1, "     1      5      1     E1\t~RST\t\tActive-low reset input");
		// firstPin.add(2, 1, "                           \tNMI\t\tNonmaskable interrupt input");
		// firstPin.add(3, 1, "                           \tSBWTDIO\t\tSpy-Bi-Wire data input/output");

		printShortcuts();

		int l = 20;
		Window &statusWin = standardScreen();
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

		top.paint();
		defaultSet.paint();
		newSet.paint();

		// initial state: open search window
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST_MODEL_LENGTH);
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);
		ui::drawTopWindow(top, selectedDS, totals);

		const vector<string> pkgs = db::findPackagesByDatasheet(db, selectedDS.id);
		// TODO: really should be possible to re-order packages and possibly other things!
		// other centered screen to quickly do this?
		// idea: quick-n-dirt: input field with number, default numbers start from # pkgs+1 (not shown in fields though)
		// i.e. 4 packages DA, N, RHB, YXW: "weight" 5,6,7,8; putting # in any field makes easy first/second etc?
		// set N to 1, becomes N, DA, RHB, YXW; but what happens when setting to 2 instead of 1? NOT AS EXPECTED becomes first
		// maybe just default indices and when filled, swap? dunno, also error-prone
		ui::PinSetView vw(pkgs);
		// TODO: get pins & signals from DB
		ui::drawPinSet(pins, vw);
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

		// set_field_type(field[0], TYPE_ALNUM);
		// set_field_type(field[1], TYPE_INTEGER);
		wgetch(pins); // just here to prevent application exit for partial mock-up
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
void printShortcuts() {
	const int LINE = 5;

	// TODO C++ knowledge: will only work as reference, not copy; WHY?????
	Window &hotkeyWin = standardScreen();

	hotkeyWin.moveCursor(LINE, 0);
	printShortcut(hotkeyWin, "ESC", "QUIT");
	printShortcut(hotkeyWin, "F1", "Help");
	printShortcut(hotkeyWin, "F2", "Search");
	printShortcut(hotkeyWin, "PgUp/PgDn", "Up/Down");
	printShortcut(hotkeyWin, "Ctrl+e", "Edit Mode");
	printShortcut(hotkeyWin, "Ctrl+s", "Save");
	printShortcut(hotkeyWin, "F5-F9", "Set #");
}
