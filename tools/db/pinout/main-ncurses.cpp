#include <iostream>

#include "sqlite3.h"
#include "curses.h"
#include "form.h"
#include "ncurses.h"

using namespace std;

void autofillDatasheet() {

}

int main()
{
	FIELD *field[3];
	FORM *my_form;
	int ch;

	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize few color pairs */
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	/* Initialize the fields */
	field[0] = new_field(1, 20, 1, 20, 0, 0);
	field[1] = new_field(1, 20, 2, 20, 0, 0);
	field[2] = NULL;

	/* Set field options */
	set_field_fore(field[0], COLOR_PAIR(1)); /* Put the field with blue background */
	set_field_back(field[0], COLOR_PAIR(2)); /* and white foreground (characters */
	/* are printed in white 	*/
	field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
	/* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE);
	field_opts_off(field[1], O_AUTOSKIP | O_DYNAMIC_JUSTIFY);

	// set_field_type(field[0], TYPE_ALNUM);
	// set_field_type(field[1], TYPE_INTEGER);

	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();

	set_current_field(my_form, field[0]); /* Set focus to the colored field */
	mvprintw(1, 2, "Datasheet");
	mvprintw(2, 2, "Device");
	mvprintw(3, 2, "Package Drawings");
	mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys OR TAB/BTAB to switch between fields");
	refresh();

	/* Loop through to get user requests */
	while ( (ch = getch()) < KEY_F(1) || ch > KEY_F(12) ) {
		switch ( ch ) {
			case KEY_DOWN:
			case 9:
				// TODO: TAB doesn't work, BTAB (back-tab does)...
				// using code 9 does too, no key value? odd
				// it's probably in some other file?
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
			case KEY_BTAB:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			// case KEY_LEFT:
			// 	form_driver(my_form, REQ_PREV_CHAR);
			// 	break;
			// case KEY_RIGHT:
			// 	// TODO: moves beyond contents as if moving in empty buffer
			// 	// REQ_END_FIELD does it correctly though
			// 	form_driver(my_form, REQ_RIGHT_CHAR);
			// 	break;
			case KEY_BACKSPACE:
			case 127: // 127 = 0177; returned for backspace in Konsole? why?
				// TODO: moves to next field if current field is empty ...
				form_driver(my_form, REQ_DEL_PREV);
				break;
				// if no navigation (left/right), delete still needed for last character in field!
			case KEY_DC: // delete character
				// Konsole and VT
				form_driver(my_form, REQ_DEL_CHAR);
				break;
				// case KEY_END:
				// 	form_driver(my_form, REQ_END_FIELD);
				// 	break;
				// case KEY_HOME:
				// 	form_driver(my_form, REQ_BEG_FIELD);
				// 	break;
			case ' ': // do not allow space
				break;
			default:
				/* If this is a normal character, it gets Printed */
				form_driver(my_form, ch);
				cout << ch << ' '; // for debugging, print character numbers for now
				break;
		}
	}

	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]);

	endwin();
	return EXIT_SUCCESS;
}
