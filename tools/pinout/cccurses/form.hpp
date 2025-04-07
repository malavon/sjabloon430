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

struct FormSize {
	int columns;
	int rows;
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

  private:
	void toggleOption(int option, const Toggle toggle) {
		if ( toggle == ON ) {
			field_opts_on(ptr, option);
		} else {
			field_opts_off(ptr, option);
		}
	}

  public:
	void optionAutoSkip(const Toggle toggle) {
		toggleOption(O_AUTOSKIP, toggle);
	}

	void optionActive(const Toggle toggle) {
		toggleOption(O_ACTIVE, toggle);
	}

	void optionsActiveAndEditable(const Toggle toggle) {
		toggleOption(O_ACTIVE | O_EDIT, toggle);
	}

	void optionEditable(const Toggle toggle) {
		toggleOption(O_EDIT, toggle);
	}

	void justify(const int justification) {
		set_field_just(ptr, justification);
	}

	void paint(int row, int col) {
		// can only move when NOT connected to form ...
		int rc = move_field(ptr, row, col);
		// if ( rc != E_OK ) {
		// 	std::cout << "Error " << printRC(rc) << endl;
		// }

		assert(rc != E_OK);
	}

	// TODO: more than just a pair?
	// TODO: also, fore & back are difficult to understand; empty/filled?
	void setColors(int fore = COLOR_PAIR_FORM_SELECTED, int back = COLOR_PAIR_FORM_VALID) {
		set_field_fore(ptr, COLOR_PAIR(fore));
		set_field_back(ptr, COLOR_PAIR(back));
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

	void setBuffer(const string newBuffer) {
		set_field_buffer(ptr, 0, newBuffer.c_str());
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

/* Temporary very restrictive callback/event handler */
class FormEventHandler {
  public:
	// todo: return values or not?
	void onNextField() { }

	void onPreviousField() { }
};

namespace internal {
template<class EH>
class FormEventHandlerWrapper {
  public:
	FormEventHandlerWrapper(EH &eventHandler, FORM *cursesForm) : formptr(cursesForm), handler(eventHandler) { }

  public:
	FORM *formptr;
	EH &handler;
};
}

using namespace internal;

class SimpleFormKeyEventConsumer : public KeyEventConsumer<FORM *> {
  public:
	static KeyFeedback keyBackTab(FORM *ctx) {
		/* Go to previous field */
		form_driver(ctx, REQ_PREV_FIELD);
		form_driver(ctx, REQ_END_LINE);
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyBackspace(FORM *ctx) {
		form_driver(ctx, REQ_DEL_PREV);
		// TEST: if impossible to prevent REQ_DEL_PREV from changing to previous field
		// second best is to jump to end of field then?
		form_driver(ctx, REQ_END_FIELD);
		return FEEDBACK_CONTINUE;
	}

	static KeyFeedback keyCharacter(FORM *ctx, const int ch) {
		form_driver(ctx, ch);
		cout << static_cast<int>(ch) << ' '; // for debugging, print character numbers for now
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

	static KeyFeedback keyWhitespace(FORM *ctx, const int ch) {
		form_driver(ctx, ch);
		cout << ch << ' '; // for debugging, print character numbers for now
		return FEEDBACK_CONTINUE;
	}
};

template<class EH>
class EventingFormKeyEventConsumer
    : public KeyEventConsumer<FormEventHandlerWrapper<EH>> /*, private SimpleFormKeyEventConsumer*/ {
  public:
	static KeyFeedback keyBackTab(FormEventHandlerWrapper<EH> &wrapper) {
		KeyFeedback res = SimpleFormKeyEventConsumer::keyBackTab(wrapper.formptr);
		// this needs to be AFTER the form handling, otherwise buffer is not changed!
		wrapper.handler.onPreviousField();
		return res;
	}

	static KeyFeedback keyBackspace(FormEventHandlerWrapper<EH> &wrapper) {
		return SimpleFormKeyEventConsumer::keyBackspace(wrapper.formptr);
	}

	static KeyFeedback keyCharacter(FormEventHandlerWrapper<EH> &wrapper, const int ch) {
		return SimpleFormKeyEventConsumer::keyCharacter(wrapper.formptr, ch);
	}

	static KeyFeedback keyDelete(FormEventHandlerWrapper<EH> &wrapper) {
		return SimpleFormKeyEventConsumer::keyDelete(wrapper.formptr);
	}

	// TODO: would be more logical to move to next field after validation?
	static KeyFeedback keyEnter(FormEventHandlerWrapper<EH> &wrapper) {
		return SimpleFormKeyEventConsumer::keyEnter(wrapper.formptr);
	}

	// KeyFeedback keyLeftArrow(FORM* ctx) {
	// 	return ;
	// }

	// allows moving through empty spaces in field, not really as expected
	// maybe fixable with dynamic field?
	// KeyFeedback keyRightArrow(FORM* ctx) {
	// 	return ;
	// }

	static KeyFeedback keyTab(FormEventHandlerWrapper<EH> &wrapper) {
		KeyFeedback res = SimpleFormKeyEventConsumer::keyTab(wrapper.formptr);
		// this needs to be AFTER the form handling, otherwise buffer is not changed!
		wrapper.handler.onNextField();
		return res;
	}

	static KeyFeedback keyWhitespace(FormEventHandlerWrapper<EH> &wrapper, const int ch) {
		return SimpleFormKeyEventConsumer::keyWhitespace(wrapper.formptr, ch);
	}
};

template<class KEY>
class Form {
  public:
	/**
	 * @brief Form constructor that posts form after construction
	 * @param win
	 * @param fields
	 */
	Form(const Window &win, const Window &subForm, vector<Field> fields) : window(win) {
		fields.reserve(fields.size() + 1);
		for ( Field &fld : fields ) {
			fieldPtrs.push_back(fld.raw());
		}
		// man 3 form: ... (which must be NULL-terminated)
		fieldPtrs.push_back(nullptr);
		int rc = E_OK;
		ptr = new_form(fieldPtrs.data());
		// how to communicate errors for runtime?
		rc = errno;
		assert(rc == E_OK || rc == E_NOT_CONNECTED);
		rc = set_form_win(ptr, win.raw());
		assert(rc == E_OK);
		// TODO: this used to be inner for original 2-ptr Window
		rc = set_form_sub(ptr, subForm.raw());
		assert(rc == E_OK);
		rc = post_form(ptr);
		assert(rc == E_OK);

		// from the man-page
		// O_NL_OVERLOAD
		// 	Overload the REQ_NEW_LINE forms driver request so that calling it
		// 		at the end of a field goes to the next field.
		// 	O_BS_OVERLOAD
		// 		Overload the REQ_DEL_PREV forms driver request so that calling it
		// 			at the beginning of a field goes to the previous field.

		// these are on by default, both should be off?
		// when deleting the last character in a field, it should not suddenly select previous field
		// this is contrary to the usual "hold backspace till it's empty" behaviour
		// same for O_NL_OVERLOAD, it's not logical? TODO
		form_opts_off(ptr, O_NL_OVERLOAD | O_BS_OVERLOAD);
	}

	Form(const Window &win, vector<Field> fields) : Form(win, win, fields) { }

	~Form() {
		// TODO
		unpost_form(ptr);
		for ( FIELD *fldPtr : fieldPtrs ) {
			free_field(fldPtr);
		}
		free_form(ptr);
	}

	/**
	 * @brief addField adds a Field, requires a repost() call!
	 * @param field
	 */
	void addField(const Field &field) {
		// last element is to remain NULL/nullptr
		fieldPtrs.insert(std::prev(fieldPtrs.end(), 1), field.raw());
	}

	// useless, form has been associated to Window/subwindow already :p
	FormSize calcRequiredSize() {
		FormSize size;
		int rc = scale_form(ptr, &size.rows, &size.columns);
		assert(rc == E_OK);
		return size;
	}

	FORM *raw() const {
		return ptr;
	}

	void repost() {
		int uc = unpost_form(ptr);
		assert(uc == E_OK);

		// set form fields after unpost, may have changed
		int fc = set_form_fields(ptr, fieldPtrs.data());
		assert(fc == E_OK);

		int pc = post_form(ptr);
		assert(pc == E_OK);
	}

  protected:
	FORM *ptr;
	const Window &window;
	vector<FIELD *> fieldPtrs;

	friend class FormBuilder;
};

/** A simple pre-defined form that uses sensible key bindings for general use **/
template<class EH>
class EventEmittingForm : public Form<EventingFormKeyEventConsumer<EH>> {
  public:
	EventEmittingForm(const Window &win, vector<Field> fields) : Form<EventingFormKeyEventConsumer<EH>>(win, fields) { }

	EventEmittingForm(const Window &win, const Window &formSub, vector<Field> fields) :
	    Form<EventingFormKeyEventConsumer<EH>>(win, formSub, fields) { }

	/**
	 * @brief loop template method to include a EH object
	 * @param callback the callback
	 */
	void loop(EH &callback) {
		// TODO: there is no automatic jump to first field, so that should be implemented as well on Form
		// along with possibly a bunch of other things; not sure if a single function for each one
		FORM *localPtr = Form<EventingFormKeyEventConsumer<EH>>::ptr;
		const Window &localWin = Form<EventingFormKeyEventConsumer<EH>>::window;
		form_driver(localPtr, REQ_FIRST_FIELD);
		FormEventHandlerWrapper<EH> wrapper(callback, localPtr);
		KeyEventProducer<EventingFormKeyEventConsumer<EH>, FormEventHandlerWrapper<EH> &>::captureAndConsume(localWin,
														     wrapper);
	}
};

class SimpleForm : public Form<SimpleFormKeyEventConsumer> {
  public:
	SimpleForm(const Window &win, vector<Field> fields) : Form<SimpleFormKeyEventConsumer>(win, fields) { }

	SimpleForm(const Window &win, const Window &formSub, vector<Field> fields) :
	    Form<SimpleFormKeyEventConsumer>(win, formSub, fields) { }

	void loop() {
		// TODO: there is no automatic jump to first field, so that should be implemented as well on Form
		// along with possibly a bunch of other things; not sure if a single function for each one
		form_driver(ptr, REQ_FIRST_FIELD);
		KeyEventProducer<SimpleFormKeyEventConsumer, FORM *>::captureAndConsume(window, ptr);
	}
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

	template<class FORM_CLASS>
	FORM_CLASS build(Window &win, Window &subWin) {
		return FORM_CLASS(win, subWin, fields);
	}

  private:
	vector<Field> fields; // useful? should be in another class? layout-type thingy?
};

} // namespace cccurses

#endif // FORM_HPP
