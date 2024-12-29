#ifndef CCURSES_LAYOUT_COLUMN_LAYOUT_HPP
#define CCURSES_LAYOUT_COLUMN_LAYOUT_HPP

namespace ccurses { namespace layout {

template<int COLS>
class FixedColumnLayout<COLS> { };
}}

// version that wraps in as much or little columns as possible?
// BUT: what with form stuff?
// how to keep label & input together, without losing alignment
//	of different fields e.g.
/* 2 column layout:
 * Name			<INPUT>
 * Last name	<INPUT>
 * Street		<INPUT>
 * Number		<INPUT>
 *
 * 4-column layout for the same:
 * Name			<INPUT>		Last name	<INPUT>
 * Street		<INPUT>		Number		<INPUT>
 *
 * Flexible might result in 3 columns:
 * Name			<INPUT>		Last name
 * <INPUT>		Street		<INPUT>
 * Number		<INPUT>
 * ... which is completely garbled.
 *
 * A possible solution could be to require multiples of a certain number, e.g. 2 for forms.
 * */

template<int MULTIPLE>
class FlexColumnLayout<MULTIPLE> { };

#endif // COLUMN-LAYOUT_HPP
