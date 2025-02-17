#ifndef CCURSES_WINDOW_HPP
#define CCURSES_WINDOW_HPP

#include <string>

#include "ncurses.h"

namespace cccurses {
using namespace std;

namespace inner {
class Border { };

class BorderTitle {
  private:
	string title;
	char pre, post;
};
}

/**
 * @brief The Window class is a very simple wrapper around curses WINDOW. It's far from useful in all cases right now.
 */
class Window {
  private:
	Window() { }

  public:
	Window(unsigned int line, unsigned int col, unsigned int height, unsigned int width) {
		ptr = newwin(height, width, line, col);
		inner = subwin(ptr, height - 2, width - 2, line + 1, col + 1);
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
		waddch(inner, character);
	}

	void add(const int raw) {
		waddch(inner, raw);
	}

	void add(const string &text) {
		waddnstr(inner, text.c_str(), text.length());
	}

	void add(const char character, int attrs) {
		waddch(inner, character | attrs);
	}

	void add(const string &text, int attrs) {
		wattron(inner, attrs);
		add(text);
		wattroff(inner, attrs);
	}

	void add(const int line, const int col, const char character) {
		mvwaddch(inner, line, col, character);
	}

	void add(const int line, const int col, const int raw) {
		mvwaddch(inner, line, col, raw);
	}

	void add(const int line, const int col, const string &text) {
		// mvwaddstr(inner, line, col, text.c_str());
		mvwaddnstr(inner, line, col, text.c_str(), text.length());
	}

	void add(const int line, const int col, const char character, int attrs) {
		mvwaddch(inner, line, col, character | attrs);
	}

	void add(const int line, const int col, const string &text, int attrs) {
		wattron(inner, attrs);
		add(line, col, text);
		wattroff(inner, attrs);
	}

	void enableAttributes(const int attrs) {
		wattron(ptr, attrs);
	}

	void disableAttributes(const int attrs) {
		wattroff(ptr, attrs);
	}

	void moveCursor(const int line, const int col) {
		wmove(inner, line, col);
	}

	// these don't work, need to pass the variadic argument somehow
	// void print(const char *fmt, ...) {
	// 	wprintw(ptr, fmt);
	// }

	// void print(const int line, const int col, const char *fmt, ...) {
	// 	wmove(ptr, line, col);
	// 	wprintw(ptr, fmt);
	// }

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

	// TEMPORARY?
	WINDOW *raw() const {
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
