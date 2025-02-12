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

	void addCharacter(const char character) {
		waddch(ptr, character);
	}

	void addCharacter(const char character, int attrs) {
		waddch(ptr, character | attrs);
	}

	void addCharacter(const int line, const int col, const char character) {
		mvwaddch(ptr, line, col, character);
	}

	void addCharacter(const int line, const int col, const char character, int attrs) {
		mvwaddch(ptr, line, col, character | attrs);
	}

	void addText(const string &text) {
		waddnstr(ptr, text.c_str(), text.length());
	}

	void addText(const string &text, int attrs) {
		wattron(ptr, attrs);
		addText(text);
		wattroff(ptr, attrs);
	}

	void addText(const int line, const int col, const string &text) {
		// mvwaddstr(ptr, line, col, text.c_str());
		mvwaddnstr(ptr, line, col, text.c_str(), text.length());
	}

	void addText(const int line, const int col, const string &text, int attrs) {
		wattron(ptr, attrs);
		addText(line, col, text);
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
