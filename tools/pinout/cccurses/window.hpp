#ifndef CCURSES_WINDOW_HPP
#define CCURSES_WINDOW_HPP

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
	Window(unsigned int line, unsigned int col, unsigned int height, unsigned int width) {
		ptr = newwin(height, width, line, col);
	}

	Window(WINDOW *win) : ptr(win) { }

	Window(const Window &other) : ptr(other.ptr), title(other.title) { }

	~Window() {
		if ( ptr != nullptr ) {
			delwin(ptr); // might be dangerous with stdscr?
		}
	}

	void add(const char character) {
		waddch(ptr, character);
	}

	void add(const int raw) {
		waddch(ptr, raw);
	}

	void add(const string &text) {
		waddnstr(ptr, text.c_str(), text.length());
	}

	void add(const char character, int attrs) {
		waddch(ptr, character | attrs);
	}

	void add(const string &text, int attrs) {
		wattron(ptr, attrs);
		add(text);
		wattroff(ptr, attrs);
	}

	void add(const int line, const int col, const char character) {
		mvwaddch(ptr, line, col, character);
	}

	void add(const int line, const int col, const int raw) {
		mvwaddch(ptr, line, col, raw);
	}

	void add(const int line, const int col, const string &text) {
		// mvwaddstr(ptr, line, col, text.c_str());
		mvwaddnstr(ptr, line, col, text.c_str(), text.length());
	}

	void add(const int line, const int col, const char character, int attrs) {
		mvwaddch(ptr, line, col, character | attrs);
	}

	void add(const int line, const int col, const string &text, int attrs) {
		wattron(ptr, attrs);
		add(line, col, text);
		wattroff(ptr, attrs);
	}

	void enableAttributes(const int attrs) {
		wattron(ptr, attrs);
	}

	void disableAttributes(const int attrs) {
		wattroff(ptr, attrs);
	}

	void moveCursor(const int line, const int col) {
		wmove(ptr, line, col);
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

	// TEMPORARY?
	WINDOW *raw() const {
		return ptr;
	}

  private:
	WINDOW *ptr;
	string title;

	friend class Form;
};

} // namespace cccurses

#endif // WINDOW_HPP
