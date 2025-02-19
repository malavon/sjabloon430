#ifndef CCURSES_FORM_HPP
#define CCURSES_FORM_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "colors.hpp"
// #include "error.hpp"
#include "form.h"
#include "window.hpp"

namespace cccurses {
using namespace std;

enum Toggle { ON, OFF };

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
		ptr = new_field(height, width, row, col, offscreenLines, buffers);
		set_field_fore(ptr, COLOR_PAIR(COLOR_PAIR_FORM_SELECTED));
		set_field_back(ptr, COLOR_PAIR(COLOR_PAIR_FORM_VALID));
		/*pad character, display only, doesn't show up in buffer
		 could this be useful for validation somehow? */
		// set_field_pad(ptr, '0');
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

	void autoSkip(const Toggle toggle) {
		if ( toggle == ON ) {
			field_opts_on(ptr, O_AUTOSKIP);
		} else {
			field_opts_off(ptr, O_AUTOSKIP);
		}
	}

	void paint(int row, int col) {
		// can only move when NOT connected to form ...
		int rc = move_field(ptr, row, col);
		if ( rc != E_OK ) {
			// std::cout << "Error " << printRC(rc) << endl;
		}

		assert(rc != E_OK);
	}

	template<class T>
	const T buffer() const;

	template<>
	const string buffer<string>() const {
		char *buffer = field_buffer(ptr, 0);
		int first = -1, last = -1;
		int len = strlen(buffer) - 1;
		// find last non-whitespace character
		for ( int i = len; i >= 0 && last < 0; i-- ) {
			if ( buffer[i] != ' ' ) {
				last = i;
			}
		}
		// find first non-whitespace character
		for ( int i = 0; i < len && first < 0; i++ ) {
			if ( buffer[i] != ' ' ) {
				first = i;
			}
		}
		if ( -1 == first ) {
			// if first == -1, last also == -1
			// you, reader, do see this, right?
			return "";
		} else {
			int real = last - first + 1;
			// buffer will contain duplicates, but is trimmed in string creation
			strncpy(buffer, buffer + first, real);
			// no need to 0-terminate, real length will be used
			string str(buffer, real);
			return str;
		}
	}

	// template<>
	// const char *buffer<const char *>() {
	// 	return field_buffer(ptr, 0);
	// }

	const char *rawBuffer() const {
		return field_buffer(ptr, 0);
	}

  private:
	FIELD *ptr;

	friend class Form;
	friend class FormBuilder;
};

class Form {
  public:
	Form(const Window &win, vector<Field> fields) : window(win) {
		// man 3 form: ... (which must be NULL-terminated)
		this->fields = new FIELD *[fields.size() + 1];
		this->fields[fields.size()] = NULL;
		for ( int i = fields.size() - 1; i >= 0; i-- ) {
			this->fields[i] = fields[i].ptr;
		}
		// delegation doesn't work like this ...
		// Form(win, cFields);
		ptr = new_form(this->fields);
		// how to communicate error? assert?
		if ( errno != E_OK && errno != E_NOT_CONNECTED ) {
			// cout << "FORM ERROR " << printRC(errno) << endl;
		}
		set_form_win(ptr, win.ptr);
		set_form_sub(ptr, win.ptr); // TODO: this used to be inner for original 2-ptr Window
		post_form(ptr);
	}

	~Form() {
		// TODO
		unpost_form(ptr);
		free_form(ptr);
		for ( unsigned int i = 0; fields[i] != nullptr; i++ ) {
			free_field(fields[i]);
		}
	}

	/*  */

	// LOL
	// extremely re-usable code :p
	void loop() {
		// there is no automatic jump to first field after window paint
		form_driver(ptr, REQ_FIRST_FIELD);
		int ch;
		while ( (ch = wgetch(window.ptr)) < KEY_F(1) || ch > KEY_F(12) ) {
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
		form_driver(ptr, REQ_VALIDATION); // also copies current field's value to buffer
	}

	// TEMPORARY?
	FORM *raw() const {
		return ptr;
	}

  private:
	FORM *ptr;
	const Window &window;
	FIELD **fields;

	friend class FormBuilder;
};

// TODO: remove? post_form can happen outside of constructor
class FormBuilder {
  public:
	void addField(const Field &field) {
		fields.push_back(field);
	}

	Form build(Window &win) {
		return Form(win, fields);
	}

  private:
	vector<Field> fields; // useful? should be in another class? layout-type thingy?
};

} // namespace cccurses

#endif // FORM_HPP
