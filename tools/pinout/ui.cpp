#include "ui.hpp"

using namespace cccurses;

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

void drawTopWindow(BorderedWindow &win, const Datasheet &ds, DatabaseTotals &totals) {
	int topLine = 0;
	int topCol = 1;
	win.setTitle("Search");
	win.add(topLine + 0, topCol, "Datasheet: ");
	win.add(ds.id);
	win.add("\t\t(c)");
	win.add(ds.origDate);
	win.add(topLine + 1, topCol, "Revision:  ");
	if ( ds.rev.empty() ) {
		win.add("A"); // TODO: justify?
	} else {
		win.add(ds.rev); // TODO: justify?
		win.add("\t\t(c)");
		win.add(ds.revDate);
	}

	// currently doesn't work
	// top.print(4, 1, "DB contains: %i datasheets, %i devices, %d orderables, %i packages", totals.datasheets, totals.devices, totals.orderables,
	// totals.packages);
	win.add(topLine + 2, topCol, "DB contains: ");
	win.add(std::to_string(totals.datasheets));
	win.add(" datasheets, ");
	win.add(std::to_string(totals.devices));
	win.add(" devices, ");
	win.add(std::to_string(totals.orderables));
	win.add(" orderables, ");
	win.add(std::to_string(totals.packages));
	win.add(" packages");

	win.add(topLine + 0, topCol, "Datasheet: ");
	win.add(ds.id);

	win.paint();
}

// open a window in middle of screen, allow searching database; mock-up
Datasheet searchDatasheet(sqlite3 *db, const int widestModelLength) {
	// TODO: also add some help on this window/form fields using F1
	static const string DATASHEET_HDR("Datasheet ");
	static const string MODEL_HDR("Model ");

	const int LINE = 1;
	const int COL = 1;
	const int ML_FIELD_COL = MODEL_HDR.length() + 1;
	const int DS_FIELD_COL = max(static_cast<int>(DATASHEET_HDR.length()) + 1, ML_FIELD_COL + widestModelLength - 7);
	// 7 is fixed; all datasheets are 7 wide
	const int MENU_COL = max(DS_FIELD_COL + 7, ML_FIELD_COL + widestModelLength) + 2;

	static const int WIN_WIDTH = MENU_COL + widestModelLength + 1 + 2 /* border */;
	static const int WIN_HEIGHT = 6 + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center((LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2, WIN_HEIGHT, WIN_WIDTH);
	center.setTitle("Search");

	FormBuilder fb;
	// 7 is fixed; all datasheets are 7 wide
	Field dsField(1, 7, LINE + 0, DS_FIELD_COL);
	dsField.autoSkip(OFF);
	fb.addField(dsField);
	// from database or also hard-coded constant
	Field mdField(1, widestModelLength, LINE + 2, ML_FIELD_COL);
	mdField.autoSkip(OFF);
	fb.addField(mdField);
	SimpleForm form = fb.build<SimpleForm>(center);

	center.add(LINE + 0, COL, DATASHEET_HDR);
	center.add(LINE + 2, COL, MODEL_HDR);
	center.add(LINE + 0, MENU_COL - 1, '>');
	center.add(LINE + 0, MENU_COL, "MSP430F6458");
	center.add(LINE + 1, MENU_COL, "MSP430F6459");
	center.add(LINE + 2, MENU_COL, "MSP430F6459-HIREL");

	static const string BUTTON_TEXT = "[OPEN]";
	center.add(WIN_HEIGHT - 3, (WIN_WIDTH - BUTTON_TEXT.length()) / 2, BUTTON_TEXT, COLOR_PAIR(COLOR_PAIR_BUTTON_SELECTED));
	center.paint();

	form.loop();

	Datasheet ds;
	// note: buffer is only filled AFTER leaving the field? this isn't useful for auto-completion and in-line validation
	ds.id = dsField.buffer<string>();
	ds.id += ' ';
	ds.id += mdField.buffer<string>();
	return ds;
}

}}}} // namespace sjabloon430::tools::pinout::ui
