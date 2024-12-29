#ifndef CCURSES_FORM_HPP
#define CCURSES_FORM_HPP

#include <cassert>
#include <string>
#include <vector>

#include "error.hpp"
#include "form.h"
#include "support.hpp"
#include "window.hpp"

namespace cccurses {
using namespace std;

enum class FieldOpts : int {
	ACTIVE = O_ACTIVE,
	AUTOSKIP = O_AUTOSKIP,
	BLANK = O_BLANK,
	DYNAMIC_JUSTIFY = O_DYNAMIC_JUSTIFY,
	EDGE_INSERT_STAY = O_EDGE_INSERT_STAY,
	EDIT = O_EDIT,
	INPUT_LIMIT = O_INPUT_LIMIT,
	NO_LEFT_STRIP = O_NO_LEFT_STRIP,
	NULLOK = O_NULLOK,
	PASSOK = O_PASSOK,
	PUBLIC = O_PUBLIC,
	STATIC = O_STATIC,
	VISIBLE = O_VISIBLE,
	WRAP = O_WRAP,
};

class Field {
  public:
	// no idea what to do with offscreenLines or buffers...
	Field(int height, int width, int row, int col, int offscreenLines = 0, int buffers = 0) {
		ptr = new_field(height, width, col, row, offscreenLines, buffers);
	}

	// OR options together?
	// does not compile ... not C++ :p
	// void optionsOn(FieldOpts opt1, FieldOpts... opts) {
	// 	int result = static_cast<int>(opt1);
	// 	for ( const FieldOpts o : opts ) {
	// 		result |= static_cast<int>(o);
	// 	}
	// 	field_opts_on(ptr, result);
	// }

	// void optionsOff(FieldOpts opt1, FieldOpts... opts) {
	// 	int result = opt1;
	// 	for ( const FieldOpts o : opts ) {
	// 		result |= o;
	// 	}
	// 	field_opts_off(ptr, result);
	// }

	void optionAutoSkip(const Toggle toggle) {
		if ( toggle == Toggle::ON ) {
			field_opts_on(ptr, O_AUTOSKIP);
		} else {
			field_opts_off(ptr, O_AUTOSKIP);
		}
	}

	void paint(int row, int col) {
		// can only move when NOT connected to form ...
		int rc = move_field(ptr, row, col);
		if ( rc != E_OK ) {
			cout << "Error " << printRC(rc) << endl;
		}

		assert(rc != E_OK);
	}

  private:
	FIELD *ptr;
};

class Form {
  public:
	Form(const Window &window) : window(window) {
		ptr = new_form(NULL /* FIELDS */);
		// post form
		// TODO: win should know about? what happens when window is deleted?
		set_form_win(ptr, window.ptr);
	}

	// wow, user-friendly :p
	// just like all other line-col based things?
	// also, following curses Y-first params
	void addField(int height, int width, int row, int col) {
		formFields.push_back(new_field(height, width, row, col, 0, 0));
	}

	void addField(const Field &field) {
		fields.push_back(field);
		window.paint();
	}

	// LOL
	// extremely re-usable code :p
	void loop() {
		int ch;
		while ( (ch = getch()) < KEY_F(1) || ch > KEY_F(12) ) {
			switch ( ch ) {
				case KEY_DOWN:
				case 9:
					// TODO: TAB doesn't work, BTAB (back-tab does)...
					// using code 9 does too, no key value? odd
					// it's probably in some other file?
					form_driver(ptr, REQ_NEXT_FIELD);
					/* Go to the end of the present buffer */
					/* Leaves nicely at the last character */
					form_driver(ptr, REQ_END_LINE);
					break;
				case KEY_UP:
				case KEY_BTAB:
					/* Go to previous field */
					form_driver(ptr, REQ_PREV_FIELD);
					form_driver(ptr, REQ_END_LINE);
					break;
				// case KEY_LEFT:
				// 	form_driver(ptr, REQ_PREV_CHAR);
				// 	break;
				// case KEY_RIGHT:
				// 	// TODO: moves beyond contents as if moving in empty buffer
				// 	// REQ_END_FIELD does it correctly though
				// 	form_driver(ptr, REQ_RIGHT_CHAR);
				// 	break;
				case KEY_BACKSPACE:
				case 127: // 127 = 0177; returned for backspace in Konsole? why?
					// TODO: moves to next field if current field is empty ...
					form_driver(ptr, REQ_DEL_PREV);
					break;
					// if no navigation (left/right), delete still needed for last character in field!
				case KEY_DC: // delete character
					// Konsole and VT
					form_driver(ptr, REQ_DEL_CHAR);
					break;
					// case KEY_END:
					// 	form_driver(ptr, REQ_END_FIELD);
					// 	break;
					// case KEY_HOME:
					// 	form_driver(ptr, REQ_BEG_FIELD);
					// 	break;
				case ' ': // do not allow space
					break;
				default:
					/* If this is a normal character, it gets Printed */
					form_driver(ptr, ch);
					cout << ch << ' '; // for debugging, print character numbers for now
					break;
			}
		}
	}

	~Form() {
		// set_form_win(ptr, nullptr);
		free_form(ptr);
	}

  private:
	FORM *ptr;
	const Window &window;
	vector<FIELD *> formFields; // useful?
	vector<Field> fields;	    // useful? should be in another class? layout-type thingy?
};

} // namespace cccurses

#endif // FORM_HPP
