#ifndef CCURSES_COLORS_HPP
#define CCURSES_COLORS_HPP

#include "ncurses.h"

namespace cccurses {

enum PredefinedColorPairs {
	COLOR_PAIR_FORM_SELECTED = 1,
	COLOR_PAIR_FORM_INVALID,
	COLOR_PAIR_FORM_VALID,
	COLOR_PAIR_BUTTON_DEFAULT,
	COLOR_PAIR_BUTTON_SELECTED
};

namespace internal {

void defineColors() {
	// TODO: FreeBSD terminals do not allow changing colors? :(
	if ( has_colors() && can_change_color() ) {
		init_color(8, 0xed, 0xee, 0x1e);
	}
}

void defineColorPairs() {
	/* Initialize few hard-coded color pairs */
	init_pair(COLOR_PAIR_FORM_SELECTED, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_PAIR_FORM_INVALID, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_PAIR_FORM_VALID, COLOR_WHITE, COLOR_BLUE);

	init_pair(COLOR_PAIR_BUTTON_DEFAULT, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_PAIR_BUTTON_SELECTED, COLOR_WHITE, COLOR_BLUE);
}

void initColors() {
	if ( has_colors() ) {
		start_color();
	}
	defineColors();
	defineColorPairs();
}

} // namespace internal
} // namespace cccurses

#endif // CCURSES_COLORS_HPP
