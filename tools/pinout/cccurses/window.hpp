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
		keypad(ptr, true);
	}

	Window(const Window &other) : ptr(other.ptr) { }

	// shouldn't really be here, it only exists for wrapping stdscr
	Window(WINDOW *win) : ptr(win) { }

	~Window() {
		clear();
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

	void paint() const {
		wrefresh(ptr);
	}

	void clear() {
		wclear(ptr);
		wrefresh(ptr);
	}

	operator WINDOW *() const {
		return ptr;
	}

  protected:
	WINDOW *ptr;

	friend class Form;
};

// Window that keeps a separate subwindow (or derived window) pointer
/* A Window that has a statically defined border which can be enabled/disabled when required.
 * In order to fix wrapping a subwindow (or more correct: a derived window) is created as
 * the target for everything to be added. */
class BorderedWindow : public Window {
  public:
	BorderedWindow(unsigned int height, unsigned int width, unsigned int line, unsigned int col) :
	    Window(height, width, line, col) {
		outer = ptr;
		// replace original pointer with the derived window inside the border
		ptr = derwin(outer, height - 2, width - 2, 1, 1);
		assert(nullptr != ptr);
		keypad(ptr, true);
	}

	BorderedWindow(const BorderedWindow &o) : Window(o) {
		outer = o.outer;
		title = o.title;
	}

	~BorderedWindow() {
		clear();
		if ( outer != nullptr ) {
			delete outer;
		}
	}

	void setTitle(const string &title) {
		this->title = title;
	}

	void paint() const {
		int rc = wborder(outer, 0, 0, 0, 0, 0, 0, 0, 0);
		assert(OK == rc);
		if ( !title.empty() ) {
			rc = mvwaddnstr(outer, 0, 2, title.c_str(), title.length());
			assert(OK == rc);
		}
		rc = wrefresh(outer);
		assert(OK == rc);
		Window::paint();
	}

	void clear() {
		Window::clear();
		wclear(outer);
		wrefresh(outer);
	}

  private:
	/* outer Window including the border;
	 * Window::ptr is the inner because it's the main target */
	WINDOW *outer;
	string title;
	// border chars?
};

} // namespace cccurses

#endif // WINDOW_HPP
