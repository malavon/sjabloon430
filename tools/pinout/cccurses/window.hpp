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
	// default constructor: for flex window?
	Window() { }

  public:
	Window(unsigned int height, unsigned int width, unsigned int row, unsigned int col) {
		ptr = newwin(height, width, row, col);
		assert(nullptr != ptr);
	}

	~Window() {
		if ( ptr != nullptr ) {
			delwin(ptr);
		}
	}

	void addText(const string &text) {
		waddnstr(ptr, text.c_str(), text.length());
	}

	void addText(const string &text, int attrs) {
		wattron(ptr, attrs);
		addText(text);
		wattroff(ptr, attrs);
	}

	void addText(const int y, const int x, const string &text) {
		// mvwaddstr(ptr, y, x, text.c_str());
		mvwaddnstr(ptr, y, x, text.c_str(), text.length());
	}

	void addText(const int y, const int x, const string &text, int attrs) {
		wattron(ptr, attrs);
		addText(y, x, text);
		wattroff(ptr, attrs);
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
