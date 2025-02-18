
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

void drawTopWindow(cccurses::BorderedWindow &, const db::Datasheet &, db::DatabaseTotals &);
db::Datasheet searchDatasheet(sqlite3 *db); // todo: return object containing dates as well
void printShortcuts();

static const int WIDEST_MODEL_LENGTH = strlen("MSP430F6459-HIREL"); /* hardcoded longest model */
static const int WIN_TOP_HEIGHT = 5;
static const int WIN_CONFIGSET_WIDTH = WIDEST_MODEL_LENGTH + 2 /* indent */ + 2 /* borders */;

// 7 is fixed; all datasheets are 7 wide
static const int FIELD_WIDTH_DATASHEET = 7;

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
		db::Datasheet selectedDS = searchDatasheet(db);

		drawTopWindow(top, selectedDS, totals);
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
db::Datasheet searchDatasheet(sqlite3 *) {
	// TODO: also add some help on this window/form fields using F1
	static const string DATASHEET_HDR("Datasheet ");
	static const string MODEL_HDR("Model ");

	const int LINE = 1;
	const int COL = 1;
	const int ML_FIELD_COL = MODEL_HDR.length() + 1;
	const int DS_FIELD_COL =
		max<int>(DATASHEET_HDR.length() + 1, ML_FIELD_COL + WIDEST_MODEL_LENGTH - FIELD_WIDTH_DATASHEET);
	// 7 is fixed; all datasheets are 7 wide
	const int MENU_COL = max(DS_FIELD_COL + FIELD_WIDTH_DATASHEET, ML_FIELD_COL + WIDEST_MODEL_LENGTH) + 2;

	static const int WIN_WIDTH = MENU_COL + WIDEST_MODEL_LENGTH + 1 + 2 /* border */;
	static const int WIN_HEIGHT = 6 + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Search");

	FormBuilder fb;
	Field dsField(1, FIELD_WIDTH_DATASHEET, LINE + 0, DS_FIELD_COL);
	dsField.optionAutoSkip(Toggle::OFF);
	fb.addField(dsField);
	// from database or also hard-coded constant
	Field mdField(1, WIDEST_MODEL_LENGTH, LINE + 2, ML_FIELD_COL);
	mdField.optionAutoSkip(Toggle::OFF);
	fb.addField(mdField);
	Form form = fb.build(center);
	center.add(LINE + 0, COL, DATASHEET_HDR);
	center.add(LINE + 2, COL, MODEL_HDR);
	center.add(LINE + 0, MENU_COL - 1, '>');
	center.add(LINE + 0, MENU_COL, "MSP430F6458");
	center.add(LINE + 1, MENU_COL, "MSP430F6459");
	center.add(LINE + 2, MENU_COL, "MSP430F6459-HIREL");

	static const string BUTTON_TEXT = "[OPEN]";
	center.add(WIN_HEIGHT - 3, (WIN_WIDTH - BUTTON_TEXT.length()) / 2, BUTTON_TEXT, COLOR_PAIR(COLOR_PAIR_BUTTON_SELECTED));
	center.paint();

	form.loop();

	db::Datasheet ds;
	// note: buffer is only filled AFTER leaving the field? this isn't useful for auto-completion and in-line validation
	ds.id = dsField.buffer<string>();
	ds.id += ' ';
	ds.id += mdField.buffer<string>();
	return ds;
}

void drawTopWindow(cccurses::BorderedWindow &win, const db::Datasheet &ds, db::DatabaseTotals &totals) {
	int topLine = 0;
	int topCol = 1;
	win.setTitle("Search");
	win.add(topLine + 0, topCol, "Datasheet: ");
	win.add(ds.id);
	win.add("\t\t(c)");
	win.add(ds.origDate);
	win.add(topLine + 1, topCol, "Revision:  ");
	if ( ds.rev.empty() ) {
		win.add("A"); // TODO: justify?
	} else {
		win.add(ds.rev); // TODO: justify?
		win.add("\t\t(c)");
		win.add(ds.revDate);
	}

	// currently doesn't work
	// top.print(4, 1, "DB contains: %i datasheets, %i devices, %d orderables, %i packages", totals.datasheets, totals.devices, totals.orderables,
	// totals.packages);
	win.add(topLine + 2, topCol, "DB contains: ");
	win.add(std::to_string(totals.datasheets));
	win.add(" datasheets, ");
	win.add(std::to_string(totals.devices));
	win.add(" devices, ");
	win.add(std::to_string(totals.orderables));
	win.add(" orderables, ");
	win.add(std::to_string(totals.packages));
	win.add(" packages");

	win.add(topLine + 0, topCol, "Datasheet: ");
	win.add(ds.id);

	win.paint();
}
