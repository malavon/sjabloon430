
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
		Window firstPin(6, COLS - WIN_CONFIGSET_WIDTH, 7, 0);
		Window secondPin(5, COLS - WIN_CONFIGSET_WIDTH, 12, 0);

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
		firstPin.add(0, 1, " RHB32   DA32  RGE24  YQW24\tSignal\t\tDescription");
		firstPin.add(1, 1, "     1      5      1     E1\t~RST\t\tActive-low reset input");
		firstPin.add(2, 1, "                           \tNMI\t\tNonmaskable interrupt input");
		firstPin.add(3, 1, "                           \tSBWTDIO\t\tSpy-Bi-Wire data input/output");

		secondPin.add(0, 1, " RHB32   DA32  RGE24  YQW24\tSignal\t\tDescription");
		secondPin.add(1, 1, "     2      6      2     D2\tTEST\t\tTest Mode pin");
		secondPin.add(2, 1, "                           \tSBWTCK\t\tSpy-Bi-Wire input clock ");

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
		firstPin.paint();
		secondPin.paint();

		// initial state: open search window
		db::Datasheet selectedDS = ui::searchDatasheet(db, WIDEST_MODEL_LENGTH);

		ui::drawTopWindow(top, selectedDS, totals);

		// set_field_type(field[0], TYPE_ALNUM);
		// set_field_type(field[1], TYPE_INTEGER);
	}

	endwin(); // important: restores terminal

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
