#ifndef CCURSES_COLORS_HPP
#define CCURSES_COLORS_HPP

#include "ncurses.h"

namespace cccurses { namespace internal {

enum PredefinedColorPairs { COLOR_PAIR_FORM_SELECTED = 1, COLOR_PAIR_FORM_INVALID, COLOR_PAIR_FORM_VALID };

void initColors() {
	start_color();

	/* Initialize few hard-coded color pairs */
	init_pair(COLOR_PAIR_FORM_SELECTED, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_PAIR_FORM_INVALID, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_PAIR_FORM_VALID, COLOR_WHITE, COLOR_BLUE);
}

}}

#endif // CCURSES_COLORS_HPP
