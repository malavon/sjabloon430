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
	Window(unsigned int height, unsigned int width, unsigned int line, unsigned int col) {
		ptr = newwin(height, width, line, col);
		keypad(ptr, true);
	}

	Window(const Window &other) : ptr(other.ptr) { }

	// shouldn't really be here, it only exists for wrapping stdscr
	Window(WINDOW *win) : ptr(win) { }

	~Window() {
		erase();
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

	Window deriveWindow(unsigned int height, unsigned int width, unsigned int line, unsigned int col) {
		WINDOW *der = derwin(ptr, height, width, line, col);
		// assert(der == nullptr);
		keypad(der, true); // TODO? part of form? or not?
		return Window(der);
	}

	void erase() {
		werase(ptr);
		wrefresh(ptr);
	}

	void moveCursor(const int line, const int col) {
		wmove(ptr, line, col);
	}

	// these don't work, need to pass the variadic argument somehow
	// void print(const char *fmt, ...) {
	// 	wprintw(ptr, fmt);
	// }

	// void print(const int line, const int col, const char *fmt, ...) {
	// 	wmove(ptr, line, col);
	// 	wprintw(ptr, fmt);
	// }

	void paint() const {
		wrefresh(ptr);
	}

	// TEMPORARY?
	WINDOW *raw() const {
		return ptr;
	}

  protected:
	WINDOW *ptr;

	// friend class Form;
};

// Window that keeps a separate subwindow (or derived window) pointer
/* A Window that has a statically defined border which can be enabled/disabled when required.
 * In order to fix wrapping a subwindow (or more correct: a derived window) is created as
 * the target for everything to be added. */
class BorderedWindow : public Window {
  public:
	BorderedWindow(unsigned int height, unsigned int width, unsigned int line, unsigned int col) : Window(height, width, line, col) {
		outer = ptr;
		// replace original pointer with the derived window inside the border
		ptr = derwin(outer, height - 2, width - 2, 1, 1);
		keypad(ptr, true);
	}

	~BorderedWindow() {
		clear();
		if ( outer != nullptr ) {
			delete outer;
		}
	}

	void erase() {
		touchwin(outer);
		Window::erase();
		werase(outer);
		wrefresh(outer);
	}

	void paint() const {
		touchwin(outer);
		wborder(outer, 0, 0, 0, 0, 0, 0, 0, 0);
		mvwaddnstr(outer, 0, 2, title.c_str(), title.length());
		wrefresh(outer);
		Window::paint();
	}

	void setTitle(const string &title) {
		this->title = title;
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
