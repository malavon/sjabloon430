#ifndef CCURSES_WINDOW_HPP
#define CCURSES_WINDOW_HPP

#include <cassert>
#include <string>

#include "ncurses.h"

namespace cccurses {
using namespace std;

/**
 * @brief The Window class is a very simple wrapper around curses WINDOW. It's far from useful in all cases right now.
 */
class Window {
  private:
	Window() { }

  public:
	Window(unsigned int height, unsigned int width, unsigned int row, unsigned int col) {
		ptr = newwin(height, width, row, col);
		assert(nullptr != ptr);
	}

	Window(WINDOW *win) : ptr(win) { }

	Window(const Window &other) : ptr(other.ptr), title(other.title) { }

	~Window() {
		if ( ptr != nullptr ) {
			delwin(ptr); // might be dangerous with stdscr?
		}
	}

	// TEMPORARY functions to keep compatibility in the pinout project

	void addText(const int line, const int col, const string &text) {
		add(line, col, text);
	}

	void addText(const string &text, const int attrs = 0) {
		add(text, attrs);
	}

	void addCharacter(char kar) {
		add(kar);
	}

	// end TEMPORARY functions

	void add(const char character) {
		int rc = waddch(ptr, character);
		assert(OK == rc);
	}

	void add(const chtype raw) {
		int rc = waddch(ptr, raw);
		assert(OK == rc);
	}

	void add(const string &text) {
		int rc = waddnstr(ptr, text.c_str(), text.length());
		assert(OK == rc);
	}

	void add(const char character, int attrs) {
		int rc = waddch(ptr, character | attrs);
		assert(OK == rc);
	}

	void add(const string &text, int attrs) {
		int rc = wattron(ptr, attrs);
		assert(OK == rc);
		rc = waddnstr(ptr, text.c_str(), text.length());
		assert(OK == rc);
		rc = wattroff(ptr, attrs);
		assert(OK == rc);
	}

	void add(const int line, const int col, const char character) {
		int rc = mvwaddch(ptr, line, col, character);
		assert(OK == rc);
	}

	void add(const int line, const int col, const chtype raw) {
		int rc = mvwaddch(ptr, line, col, raw);
		assert(OK == rc);
	}

	void add(const int line, const int col, const string &text) {
		// mvwaddstr(ptr, line, col, text.c_str();
		int rc = mvwaddnstr(ptr, line, col, text.c_str(), text.length());
		assert(OK == rc);
	}

	void add(const int line, const int col, const char character, int attrs) {
		int rc = mvwaddch(ptr, line, col, character | attrs);
		assert(OK == rc);
	}

	void add(const int line, const int col, const string &text, int attrs) {
		int rc = wattron(ptr, attrs);
		assert(OK == rc);
		rc = mvwaddnstr(ptr, line, col, text.c_str(), text.length());
		assert(OK == rc);
		rc = wattroff(ptr, attrs);
		assert(OK == rc);
	}

	void enableAttributes(const int attrs) {
		int rc = wattron(ptr, attrs);
		assert(OK == rc);
	}

	void disableAttributes(const int attrs) {
		int rc = wattroff(ptr, attrs);
		assert(OK == rc);
	}

	void moveCursor(const int line, const int col) {
		int rc = wmove(ptr, line, col);
		assert(OK == rc);
	}

	void setTitle(const string &title) {
		this->title = title;
	}

	void paint() const {
		// border repaint each time? overwrites title unless written too ...
		// not efficient?
		wborder(ptr, 0, 0, 0, 0, 0, 0, 0, 0);
		mvwaddnstr(ptr, 0, 2, title.c_str(), title.length());
		wrefresh(ptr);
	}

	operator WINDOW *() const {
		return ptr;
	}

  private:
	WINDOW *ptr;
	string title;

	friend class Form;
};

} // namespace cccurses

#endif // WINDOW_HPP
