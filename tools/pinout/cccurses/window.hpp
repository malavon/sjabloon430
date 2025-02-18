#ifndef CCURSES_WINDOW_HPP
#define CCURSES_WINDOW_HPP

#include <cassert>
#include <string>

#include "ncurses.h"

namespace cccurses {
using namespace std;

namespace inner {
class Border { };

class BorderTitle {
  private:
	string title;
	// char pre, post;
};
}

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
		inner = subwin(ptr, height - 2, width - 2, row + 1, col + 1);
		assert(nullptr != ptr);
		keypad(ptr, true);
	}

	Window(const Window &other) : ptr(other.ptr), title(other.title) { }

	// shouldn't really be here, it only exists for wrapping stdscr
	Window(WINDOW *win) : ptr(win), inner(win) { }

	~Window() {
		if ( inner != nullptr ) {
			delwin(ptr);
		}
		if ( ptr != nullptr ) {
			delwin(ptr); // might be dangerous with stdscr?
		}
	}

	void add(const char character) {
		int rc = waddch(ptr, character);
		assert(OK == rc);
	}

	void add(const chtype raw) {
		int rc = waddch(ptr, raw);
		assert(OK == rc);
	}

	void add(const string &text) {
		if ( !text.empty() ) {
			int rc = waddnstr(ptr, text.c_str(), text.length());
			assert(OK == rc);
		}
	}

	void add(const char character, int attrs) {
		int rc = waddch(ptr, character | attrs);
		assert(OK == rc);
	}

	void add(const string &text, int attrs) {
		if ( !text.empty() ) {
			int rc = wattron(ptr, attrs);
			assert(OK == rc);
			rc = waddnstr(ptr, text.c_str(), text.length());
			assert(OK == rc);
			rc = wattroff(ptr, attrs);
			assert(OK == rc);
		}
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
		if ( !text.empty() ) {
			int rc = mvwaddnstr(ptr, line, col, text.c_str(), text.length());
			assert(OK == rc);
		}
	}

	void add(const int line, const int col, const char character, int attrs) {
		int rc = mvwaddch(ptr, line, col, character | attrs);
		assert(OK == rc);
	}

	void add(const int line, const int col, const string &text, int attrs) {
		if ( !text.empty() ) {
			int rc = wattron(ptr, attrs);
			assert(OK == rc);
			rc = mvwaddnstr(ptr, line, col, text.c_str(), text.length());
			assert(OK == rc);
			rc = wattroff(ptr, attrs);
			assert(OK == rc);
		}
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
		touchwin(ptr);
		wrefresh(inner);
	}

	operator WINDOW *() const {
		return ptr;
	}

  private:
	/* Window pointer, including border */
	WINDOW *ptr;
	/* Inner window, inside border */
	WINDOW *inner;

	string title;

	friend class Form;
};

} // namespace cccurses

#endif // WINDOW_HPP
