#include <iostream>

#include "sqlite3.h"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace std;

void autofillDatasheet() { }
void printShortcuts();

static const int WIN_TOP_HEIGHT = 5;

int main() {
	setlocale(LC_ALL, "");

	/* Initialize curses */
	initCurses();

	static const string WIDEST("MSP430F6459-HIREL");
	static const int MAX_WIDTH = WIDEST.length() + 2;

	{
		Window top(WIN_TOP_HEIGHT, COLS - MAX_WIDTH, 0, 0);
		Window other(10, COLS - MAX_WIDTH, WIN_TOP_HEIGHT + 1, 0);
		// base on select max(length(name) from device?
		Window right(LINES, MAX_WIDTH, 0, COLS - MAX_WIDTH);

		top.setTitle("Search");
		top.addText(1, 3, "HELLO\n");
		top.addText(2, 3, "HELLO OTHER\n");
		// whline(top.raw(), '-', 30);

		right.setTitle("Set: default");
		right.addText(1, 1, WIDEST);
		right.addText(2, 2, "PZ100");

		printShortcuts();

		top.paint();
		other.paint();
		right.paint();

		Form form(top);

		form.addField(1, 20, 1, 20);
		form.addField(1, 20, 2, 20);

		Field datasheet(1, 20, 1, 20);
		Field device(1, 20, 2, 20);

		FIELD *field[3];
		FORM *my_form;
		// int ch;

		/* Initialize few color pairs */
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_WHITE, COLOR_BLUE);

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

// print shortcuts to stdscr directly for now
void printShortcuts() {
	const int LINE = 5;
	const int FN_LEN = 3;
	const int HOTKEY_LEN = 10;
	int key = 0;
	mvaddstr(LINE, 2 + FN_LEN + HOTKEY_LEN * key++, "Quit");
	mvaddstr(LINE, 1 + FN_LEN + HOTKEY_LEN * key++, "Help");
	mvaddstr(LINE, 1 + FN_LEN + HOTKEY_LEN * key++, "Search");
	mvaddstr(LINE, 1 + FN_LEN + HOTKEY_LEN * key++, "Up/Dwn");
	mvaddstr(LINE, 1 + FN_LEN + HOTKEY_LEN * key++, "Edit");
	mvaddstr(LINE, 1 + FN_LEN + HOTKEY_LEN * key++, "Save");
	mvaddstr(LINE, 4 + FN_LEN + HOTKEY_LEN * key++, "Set #");
	mvaddstr(LINE, 2 + FN_LEN + HOTKEY_LEN * key++, "???"); // silly movie reference

	key = 0;
	attron(A_STANDOUT);
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "ESC");
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "F1");
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "F2");
	mvaddch(LINE, 1 + HOTKEY_LEN * key, ACS_UARROW);
	mvaddch(LINE, 2 + HOTKEY_LEN * key++, ACS_DARROW);
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "^e");
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "^s");
	mvaddstr(LINE, 1 + HOTKEY_LEN * key++, "F5-F9");
	mvaddch(LINE, 3 + HOTKEY_LEN * key++, ACS_PI);
}
