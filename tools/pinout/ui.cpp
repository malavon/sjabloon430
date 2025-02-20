#include "ui.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

// 7 is fixed; all datasheets are 7 wide
static const int FIELD_WIDTH_DATASHEET = 7;

// TODO: be able to render more than first pin :)
// TODO: edit/view
// TODO: window should scroll working
void drawPin(Window &win, const vector<string> &pkgs) {
	// 3 characters is enough for pin numbers, even BGA
	static const int PIN_FIELD_WIDTH = 3;
	// packages (drawing + pins) are up to 6 wide, so always format them at 6
	static const int HDR_WIDTH = 6;
	// signal is max ... TODO=
	static const int SGN_FIELD_WIDTH = 8;

	static const string SIGNAL_HDR("SIGNAL");
	static const string DESCRIPTION_HDR("DESCRIPTION");

	// static int lastPinStart = 0, lastPinEnd = 0; // TODO: not good enough, need feedback from function
	// win.moveCursor(0, 1); // TODO: based on pin #?
	// Field *pinFields = new Field[pkgs.size()];
	FormBuilder fb;
	Field *pinFields = new Field[pkgs.size()]; // needed for data? why not From Form object
	int hdrRow = 1;
	int pinRow = 2;
	int col = 0;
	for ( size_t i = 0; i < pkgs.size(); i++ ) {
		col += HDR_WIDTH + 1;

		Field fld = Field(1, PIN_FIELD_WIDTH, pinRow, col - PIN_FIELD_WIDTH);
		fld.justify(JUSTIFY_RIGHT);
		fb.addField(fld);
		pinFields[i] = fld;
	}
	col++;
	// col += 1 + std::max(static_cast<int>(SIGNAL_HDR.length()), SGN_FIELD_WIDTH) - SIGNAL_HDR.length();
	Field sgnField(1, SGN_FIELD_WIDTH, pinRow, col);
	sgnField.justify(JUSTIFY_RIGHT);
	fb.addField(sgnField);
	col += SGN_FIELD_WIDTH + 1;
	Field descField(1, 20 /*TODO*/, pinRow, col);
	fb.addField(descField);
	SimpleForm form = fb.build<SimpleForm>(win);

	// HEADER, only once every X pins?
	col = 0;
	for ( const string &pkg : pkgs ) {
		col += HDR_WIDTH + 1;
		int len = pkg.length();
		win.add(hdrRow, col - len, pkg);
	}
	win.add(hdrRow, col + SGN_FIELD_WIDTH - SIGNAL_HDR.length() + 1, SIGNAL_HDR);
	win.paint();
	form.loop();
	// TODO: check deletion
}

void drawTopWindow(BorderedWindow &win, const Datasheet &ds, DatabaseTotals &totals) {
	int topLine = 0;
	int topCol = 1;
	win.setTitle("Search");
	win.add(topLine + 0, topCol, "Datasheet: ");
	win.add(ds.id);
	win.add(topLine + 0, topCol + 24, "(c) ");
	win.add(ds.issueDate);
	win.add(topLine + 1, topCol, "Revision:  ");
	if ( ds.rev.empty() ) {
		win.add("A"); // TODO: justify?
	} else {
		win.add(ds.rev); // TODO: justify?
		win.add(topLine + 1, topCol + 24, "(c) ");
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

// open a window in middle of screen, present all options to user; return chosen datasheet
string searchDatasheet(const unordered_map<string, string> &dsModels, const int modelFieldWidth) {
	// TODO: also add some help on this window/form fields using F1
	static const string DATASHEET_HDR("Datasheet ");
	static const string MODEL_HDR("Model ");
	static const string MVP_DISCLAIMER("MVP: UPPERCASE & exact. No autocomplete.");

	const int LINE = 1;
	const int COL = 1;
	const int ML_FIELD_COL = MODEL_HDR.length() + 1;
	const int DS_FIELD_COL = max<int>(DATASHEET_HDR.length() + 1, ML_FIELD_COL + modelFieldWidth - FIELD_WIDTH_DATASHEET);
	// 7 is fixed; all datasheets are 7 wide
	const int MENU_COL = max(DS_FIELD_COL + FIELD_WIDTH_DATASHEET, ML_FIELD_COL + modelFieldWidth) + 2;

	static const int WIN_WIDTH = MENU_COL + modelFieldWidth + 1 + 2 /* border */;
	static const int WIN_HEIGHT = 6 + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Search");

	FormBuilder fb;
	// 7 is fixed; all datasheets are 7 wide
	Field dsField(1, 7, LINE + 0, DS_FIELD_COL);
	dsField.optionAutoSkip(Toggle::OFF);
	fb.addField(dsField);
	// from database or also hard-coded constant
	Field mdField(1, modelFieldWidth, LINE + 2, ML_FIELD_COL);
	mdField.optionAutoSkip(Toggle::OFF);
	fb.addField(mdField);
	SimpleForm form = fb.build<SimpleForm>(center);

	center.add(LINE - 1, COL, MVP_DISCLAIMER);
	center.add(LINE + 0, COL, DATASHEET_HDR);
	center.add(LINE + 2, COL, MODEL_HDR);

	// static const string BUTTON_TEXT = "[OPEN]"; // button not part of MVP, enter works always
	static const string BUTTON_TEXT = "[ENTER TO OPEN]"; // MVP
	center.add(WIN_HEIGHT - 3, (WIN_WIDTH - BUTTON_TEXT.length()) / 2, BUTTON_TEXT, COLOR_PAIR(COLOR_PAIR_BUTTON_SELECTED));
	center.paint();

	form.loop();

	string dsId = dsField.buffer<string>();
	string mdlId = mdField.buffer<string>();
	if ( dsId.empty() ) {
		assert(!mdlId.empty());
		if ( dsModels.count(mdlId) > 0 ) {
			dsId = dsModels.at(mdlId);
		}
	}
	return dsId;
}

}}}} // namespace sjabloon430::tools::pinout::ui
