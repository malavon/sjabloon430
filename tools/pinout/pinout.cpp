
#include <iostream>
#include <set>

#include "database-files.hpp"
#include "database.hpp"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace sjabloon430::tools::pinout;
namespace dbf = sjabloon430::tools::db;

void searchDatasheet(sqlite3 *db);
void printShortcuts();

static const int WIDEST_MODEL_LENGTH = strlen("MSP430F6459-HIREL"); /* hardcoded longest model */
static const int WIN_TOP_HEIGHT = 5;

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
	static const int MAX_WIDTH = WIDEST_MODEL_LENGTH + MODEL_INDENT + 2 /*border*/;

	{
		Window top(WIN_TOP_HEIGHT, COLS - MAX_WIDTH, 0, 0);

		Window defaultSet(10, MAX_WIDTH, 0, COLS - MAX_WIDTH);
		Window newSet(3, MAX_WIDTH, 10, COLS - MAX_WIDTH);
		// TODO: no border, separate with hline or something?
		Window firstPin(6, COLS - MAX_WIDTH, 6, 0);
		Window secondPin(5, COLS - MAX_WIDTH, 12, 0);

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
		newSet.add(1, 1, "F5: Create new set");

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

		int topLine = 0;
		int topCol = 1;
		top.setTitle("Search");
		top.add(topLine + 0, topCol, "Datasheet: SLAS942\t(c) 11/2015");
		top.add(topLine + 1, topCol, "Revision:  E\t\t(c) 12/2019");
		// currently doesn't work
		// top.print(4, 1, "DB contains: %i datasheets, %i devices, %d orderables, %i packages", totals.datasheets, totals.devices, totals.orderables,
		// totals.packages);
		top.add(topLine + 2, topCol, "DB contains: ");
		top.add(std::to_string(totals.datasheets));
		top.add(" datasheets, ");
		top.add(std::to_string(totals.devices));
		top.add(" devices, ");
		top.add(std::to_string(totals.orderables));
		top.add(" orderables, ");
		top.add(std::to_string(totals.packages));
		top.add(" packages");

		top.paint();
		defaultSet.paint();
		newSet.paint();
		firstPin.paint();
		secondPin.paint();

		// initial state: open search window
		searchDatasheet(db);

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

// open a window in middle of screen, allow searching database; mock-up
void searchDatasheet(sqlite3 *db) {
	// TODO: also add some help on this window/form fields using F1
	static const string DATASHEET_HDR("Datasheet ");
	static const string MODEL_HDR("Model ");
	static const int MAX_WIDTH =
	    1 + DATASHEET_HDR.length() + (WIDEST_MODEL_LENGTH + 1) * 2 + 1 /* space */ + 2 /* border */;
	static const int MAX_HEIGHT = 6 + 2 /* border */;

	const int line = 1;
	const int hdrCol = 1;
	const int fieldCol = hdrCol + DATASHEET_HDR.length();
	const int menuCol = fieldCol + WIDEST_MODEL_LENGTH + 2;

	// TODO: doesn't care about resizing or too small a screen
	Window center(MAX_HEIGHT, MAX_WIDTH, (LINES - MAX_HEIGHT) / 2, (COLS - MAX_WIDTH) / 2);
	center.setTitle("Search");

	FormBuilder fb;
	// 7 is fixed; all datasheets are 7 wide
	Field dsField(1, 7, line + 0, fieldCol);
	dsField.optionAutoSkip(Toggle::OFF);
	// from database or also hard-coded constant
	Field mdField(1, WIDEST_MODEL_LENGTH, line + 2, fieldCol);
	mdField.optionAutoSkip(Toggle::OFF);
	fb.addField(dsField);
	fb.addField(mdField);
	Form form = fb.build(center);
	center.add(line + 0, hdrCol, DATASHEET_HDR);
	center.add(line + 2, hdrCol, MODEL_HDR);
	center.add(line + 0, menuCol - 1, '>');
	center.add(line + 0, menuCol, "MSP430F6458");
	center.add(line + 1, menuCol, "MSP430F6459");
	center.add(line + 2, menuCol, "MSP430F6459-HIREL");

	static const string BUTTON_TEXT = "[OPEN]";
	center.add(MAX_HEIGHT - 3, (MAX_WIDTH - BUTTON_TEXT.length()) / 2, BUTTON_TEXT, COLOR_PAIR(COLOR_PAIR_BUTTON_SELECTED));
	center.paint();

	form.loop();
}
