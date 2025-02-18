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

} // namespace cccurses

#endif // CCURSES_COLORS_HPP
