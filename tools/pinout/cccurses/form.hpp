#ifndef CCURSES_FORM_HPP
#define CCURSES_FORM_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "colors.hpp"
// #include "error.hpp"
#include "form.h"
#include "input.hpp"
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
	Field() { }

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

	void justify(const int justification) {
		set_field_just(ptr, justification);
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

	// TODO: shared with template Form
	// TODO: friend class Form<T> instead
	FIELD *raw() const {
		return ptr;
	}

  private:
	FIELD *ptr;

	// friend class Form<class>; // how to?
	// friend class FormBuilder;
};

class DefaultFormKeyEventDelegate : public KeyEventDelegate<FORM *> {
  public:
	DefaultFormKeyEventDelegate(FORM *form) : ptr(form) { }

	static KeyFeedback keyBackTab(FORM *ctx) {
		/* Go to previous field */
		form_driver(ctx, REQ_PREV_FIELD);
		form_driver(ctx, REQ_END_LINE);
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyBackspace(FORM *ctx) {
		form_driver(ctx, REQ_DEL_PREV);
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyCharacter(FORM *ctx, const char ch) {
		form_driver(ctx, ch);
		cout << ch << ' '; // for debugging, print character numbers for now
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyDelete(FORM *ctx) {
		form_driver(ctx, REQ_DEL_CHAR);
		return FEEDBACK_CONTINUE;
	}

	// TODO: would be more logical to move to next field after validation?
	static KeyFeedback keyEnter(FORM *ctx) {
		form_driver(ctx, REQ_VALIDATION); // also copies current field's value to buffer
		return FEEDBACK_STOP;
	}

	// KeyFeedback keyLeftArrow(FORM* ctx) {
	// 	return FEEDBACK_CONTINUE;
	// }

	// allows moving through empty spaces in field, not really as expected
	// maybe fixable with dynamic field?
	// KeyFeedback keyRightArrow(FORM* ctx) {
	// form_driver(ctx, REQ_NEXT_CHAR);
	// 	return FEEDBACK_CONTINUE;
	// }

	static KeyFeedback keyTab(FORM *ctx) {
		form_driver(ctx, REQ_NEXT_FIELD);
		/* Go to the end of the present buffer */
		/* Leaves nicely at the last character */
		form_driver(ctx, REQ_END_LINE);
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyWhitespace(FORM *ctx, const char ch) {
		form_driver(ctx, ch);
		cout << ch << ' '; // for debugging, print character numbers for now
		return FEEDBACK_CONTINUE;
	}

  private:
	FORM *ptr;
};

template<class KEY>
class Form {
  public:
	Form(const Window &win, vector<Field> fields) : window(win) {
		// man 3 form: ... (which must be NULL-terminated)
		this->fields = new FIELD *[fields.size() + 1];
		this->fields[fields.size()] = NULL;
		for ( int i = fields.size() - 1; i >= 0; i-- ) {
			this->fields[i] = fields[i].raw();
		}
		// delegation doesn't work like this ...
		// Form(win, cFields);
		ptr = new_form(this->fields);
		// how to communicate error? assert?
		if ( errno != E_OK && errno != E_NOT_CONNECTED ) {
			// cout << "FORM ERROR " << printRC(errno) << endl;
		}
		set_form_win(ptr, win.raw());
		set_form_sub(ptr, win.raw()); // TODO: this used to be inner for original 2-ptr Window
		post_form(ptr);
	}

	~Form() {
		// TODO
		unpost_form(ptr);
		for ( unsigned int i = 0; fields[i] != nullptr; i++ ) {
			free_field(fields[i]);
		}
		free_form(ptr);
	}

	void loop() {
		// there is no automatic jump to first field
		form_driver(ptr, REQ_FIRST_FIELD);
		KeyEventProducer<KEY, FORM *>::captureAndDelegate(window, ptr);
	}

  private:
	FORM *ptr;
	const Window &window;
	FIELD **fields;

	friend class FormBuilder;
};

/** A simple pre-defined form that uses sensible key bindings for general use **/
class SimpleForm : public Form<DefaultFormKeyEventDelegate> {
  public:
	SimpleForm(const Window &win, vector<Field> fields) : Form<DefaultFormKeyEventDelegate>(win, fields) { }
};

// TODO: remove? post_form can happen outside of constructor
class FormBuilder {
  public:
	void addField(const Field &field) {
		fields.push_back(field);
	}

	template<class FORM_CLASS>
	FORM_CLASS build(Window &win) {
		return FORM_CLASS(win, fields);
	}

  private:
	vector<Field> fields; // useful? should be in another class? layout-type thingy?
};

} // namespace cccurses

#endif // FORM_HPP
