#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include "sqlite3.h"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

#ifndef DB_DIRECTORY
  #error "add -DDB_DIRECTORY=\"...\" to the compiler command line"
#endif

using namespace cccurses;
using namespace std;
using namespace std::filesystem;

void printShortcuts();
void importDatabase(sqlite3 *db, const path &dbDir);

int main() {
	setlocale(LC_ALL, "");

	// SQLite3 in-memory DB
	sqlite3 *db;
	// const char *database = "sjabloon430.db";
	// in-memory is preferred, but exporting should be simple, formatted and not DIY
	// if not, use a file database?
	unsigned int rc = sqlite3_open("file::memory:", &db);
	path dbDir(DB_DIRECTORY);

	if ( rc != 0 ) {
		sqlite3_close(db);
		return 1;
	}

	// importing database happens after curses setup, showing which files are read

	/* Initialize curses */
	initCurses();

	static const string WIDEST("MSP430F6459-HIREL");
	static const int MODEL_INDENT = 1;
	// base on select max(length(name)) + MODEL_INDENT + 2 from device?
	static const int MAX_WIDTH = WIDEST.length() + MODEL_INDENT + 2 /*border*/;

	{
		Window top(5, COLS - MAX_WIDTH, 0, 0);

		Window defaultSet(10, MAX_WIDTH, 0, COLS - MAX_WIDTH);
		Window newSet(3, MAX_WIDTH, 10, COLS - MAX_WIDTH);
		// TODO: no border, separate with hline or something?
		Window firstPin(6, COLS - MAX_WIDTH, 6, 0);
		Window secondPin(5, COLS - MAX_WIDTH, 12, 0);

		top.setTitle("Search");
		top.add(1, 3, "Datasheet: SLAS942\t(c) 11/2015");
		top.add(2, 3, "Revision: E\t\t(c) 12/2019");
		// whline(top.raw(), '-', 30);

		int lr = 1;
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
		firstPin.add(1, 1, " RHB32   DA32  RGE24  YQW24\tSignal\t\tDescription");
		firstPin.add(2, 1, "     1      5      1     E1\t~RST\t\tActive-low reset input");
		firstPin.add(3, 1, "                           \tNMI\t\tNonmaskable interrupt input");
		firstPin.add(4, 1, "                           \tSBWTDIO\t\tSpy-Bi-Wire data input/output");

		secondPin.add(1, 1, " RHB32   DA32  RGE24  YQW24\tSignal\t\tDescription");
		secondPin.add(2, 1, "     2      6      2     D2\tTEST\t\tTest Mode pin");
		secondPin.add(3, 1, "                           \tSBWTCK\t\tSpy-Bi-Wire input clock ");

		printShortcuts();
		importDatabase(db, dbDir);

		top.paint();
		defaultSet.paint();
		newSet.paint();
		firstPin.paint();
		secondPin.paint();

		Form form(top);

		form.addField(1, 20, 1, 20);
		form.addField(1, 20, 2, 20);

		Field datasheet(1, 20, 1, 20);
		Field device(1, 20, 2, 20);

		FIELD *field[3];
		FORM *my_form;
		int ch;

		/* Initialize few color pairs */
		// init_pair(1, COLOR_WHITE, COLOR_BLUE);
		// init_pair(2, COLOR_WHITE, COLOR_BLUE);

		/* Initialize the fields */
		// field[0] = new_field(1, 20, 1, 20, 0, 0);
		// field[1] = new_field(1, 20, 2, 20, 0, 0);
		// field[2] = NULL;
		field[0] = NULL;

		/* Set field options */
		// set_field_fore(field[0], COLOR_PAIR(1)); /* Put the field with blue background */
		// set_field_back(field[0], COLOR_PAIR(2)); /* and white foreground (characters */
		// /* are printed in white 	*/
		// field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
		// /* Field is filled up 		*/
		// set_field_back(field[1], A_UNDERLINE);
		// field_opts_off(field[1], O_AUTOSKIP | O_DYNAMIC_JUSTIFY);

		// set_field_type(field[0], TYPE_ALNUM);
		// set_field_type(field[1], TYPE_INTEGER);

		/* Create the form and post it */
		my_form = new_form(field);
		post_form(my_form);
		refresh();

		// set_current_field(my_form, field[0]); /* Set focus to the colored field */
		// mvprintw(1, 2, "Datasheet");
		// mvprintw(2, 2, "Device");
		// mvprintw(3, 2, "Package Drawings");
		// mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys OR TAB/BTAB to switch between fields");
		// refresh();

		/* Loop through to get user requests */
		form.loop();
	}

	/* Un post form and free the memory */
	// unpost_form(my_form);
	// free_form(my_form);
	// free_field(field[0]);
	// free_field(field[1]);

	endwin(); // important: restores terminal

	return EXIT_SUCCESS;
}

// maybe this should be a function shared with other programs
void importDatabase(sqlite3 *db, const path &dbDir) {
	// iterate all files, sort alphabetically/numerically and check if it's actually a (SQL) file
	// TODO: recursive, should also include pinout per device later, simplifies files
	set<path> files;
	directory_iterator it(dbDir);
	for ( const directory_entry &dir_entry : it ) {
		if ( dir_entry.is_regular_file() && dir_entry.path().extension() == ".sql" ) {
			files.insert(dir_entry.path());
		}
	}

	Window &statusWin = standardScreen();
	// insert all files into in-memory DB
	// print to stdscr as status messages before basically beginning to use the application
	// TODO: line right under top window (no pinset is shown from application start)
	int l = 20;
	statusWin.add(l++, 0, "Imported SQLite DB from files:");
	for ( const path &p : files ) {
		statusWin.add(l++, 2, '"');
		statusWin.add(p.filename());
		statusWin.add('"');

		// read file completely into memory
		std::ifstream input(p);
		std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

		char *errorMsg;
		sqlite3_exec(db, content.c_str(), nullptr /*NULL callback is valid?*/, nullptr, &errorMsg);

		if ( errorMsg != nullptr ) {
			statusWin.add(' ');
			statusWin.add(errorMsg);
			sqlite3_free(errorMsg);
		}
	}
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
