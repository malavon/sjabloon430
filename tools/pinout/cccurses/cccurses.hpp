#ifndef CCURSES_HPP
#define CCURSES_HPP

#include "ncurses.h"
#include "window.hpp"

namespace cccurses {

// WILL NOT WORK AS STATIC VARIABLE
// Window standardScreen(nullptr);

/*
 * Temporary init function, without any choice basically. It's all I need right now.
 * */
void initCurses() {
	initscr();
	start_color();
	cbreak(); // do buffer input in full-line chunks ended with Enter
	noecho(); // do not echo characters to terminal immediately
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE); // enable more keys like the numpad

	// why? no window will be painted unless this is exectured before calling wrefresh() in Window::paint();
	refresh();

	// WILL NOT WORK
	// standardScreen = Window(stdscr);
}

Window &createStandardScreen() {
	return *new Window(stdscr);
}

// class Window standard; // TODO: window from stdscr ptr
// TODO: add SIGWINCH handler?

} // namespace ccurses

#endif // CCURSES_HPP
