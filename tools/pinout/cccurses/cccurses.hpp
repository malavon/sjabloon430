#ifndef CCURSES_HPP
#define CCURSES_HPP

#include "ncurses.h"
#include "window.hpp"

namespace cccurses {

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
}

// class Window standard; // TODO: window from stdscr ptr
// TODO: add SIGWINCH handler?

} // namespace cccurses

#endif // CCURSES_HPP
