#include "ui.hpp"

using namespace cccurses;

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

class PinsetEventer : public FormEventHandler {
  public:
	void onNextField() {
		cout << " NEXT FIELD ";
	}

	void onPreviousField() {
		cout << " PREVIOUS FIELD ";
	}
};

// TODO: be able to render more than first pin :)
// TODO: edit/view
// TODO: window should scroll working
void drawPinSet(Window &win, PinSetView vw) {
	// 3 characters is enough for pin numbers, even BGA
	// using 4 is however logical, esthetic purposes 1 empty character always
	static const int PIN_FIELD_WIDTH = 4;
	// packages (drawing + pins) are up to 6 wide, so always format them at 6
	static const int HDR_WIDTH = 6;
	// signal is max ... TODO=
	static const int SGN_FIELD_WIDTH = 8;

	static const string SIGNAL_HDR("SIGNAL");
	static const string DESCRIPTION_HDR("DESCRIPTION");

	FormBuilder fb;
	Field pinFields[vw.pkgs.size()]; // needed for data? why not From Form object
	int hdrRow = 1;
	int pinRow = 1; // confusing but correct; subwindow pin row
	int col = 0;
	for ( int i = 0; i < vw.pkgs.size(); i++ ) {
		col += HDR_WIDTH + 1;

		Field fld = Field(1, PIN_FIELD_WIDTH, pinRow, col - PIN_FIELD_WIDTH);
		fld.justify(JUSTIFY_RIGHT);
		fb.addField(fld);
		pinFields[i] = fld;
	}
	int sgnCol = col + 1;
	int descCol = sgnCol + SGN_FIELD_WIDTH + 1;
	// multiple signal & info fields? hidden or something until necessary?
	// but form needs to fit inside of window AND using a subwindow may mean it's not cleared anymore?
	// or 3 signals & scroll? but less useful as viewer then
	Field sgnField(1, SGN_FIELD_WIDTH, pinRow, sgnCol);
	sgnField.justify(JUSTIFY_RIGHT);
	// test
	// make field required for validation, shouldn't allow leaving the field?
	// result; as-is empty field is allowed, BUT 3 means 2? etc wtf... odd; \0 included?
	// set_field_type(sgnField.raw(), TYPE_ALNUM, 4);
	fb.addField(sgnField);
	Field descField(1, 20 /*TODO*/, pinRow, descCol);
	fb.addField(descField);

	// is there a benefit of creating this derived/subwindow for the form?
	// clear on one is clear on the other ... useless?
	Window formWin = win.deriveWindow(10, 0, 1, 0);
	EventEmittingForm<PinsetEventer> form = fb.build<EventEmittingForm<PinsetEventer>>(formWin);

	// mock to test what happens when adding a field ...repost clears window
	Field sgnField2(1, SGN_FIELD_WIDTH, pinRow + 1, sgnCol);
	sgnField2.justify(JUSTIFY_RIGHT);
	sgnField2.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
	Field sgnField3(1, SGN_FIELD_WIDTH, pinRow + 2, sgnCol);
	sgnField3.justify(JUSTIFY_RIGHT);

	Field dscField2(1, 20, pinRow + 1, descCol);
	dscField2.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
	Field dscField3(1, 20, pinRow + 2, descCol);

	form.addField(sgnField2);
	form.addField(dscField2);
	form.addField(sgnField3);
	form.addField(dscField3);
	form.repost();

	// HEADER, only once every X pins?
	// more logically, every X signals really
	// or every pin, most pins have multiple signals; may be more useful
	// or of course # of lines or something, only once basically
	// but that would be a fixed header regardless of scrolling; maybe easiest?
	// entire window is cleared on form.repost!! should be built back up
	col = 0;
	for ( const string &pkg : vw.pkgs ) {
		col += HDR_WIDTH + 1;
		int len = pkg.length();
		win.add(hdrRow, col - len, pkg);
	}
	win.add(hdrRow, sgnCol, SIGNAL_HDR);
	win.add(hdrRow, descCol, DESCRIPTION_HDR);
	win.paint();

	PinsetEventer pev;

	form.loop(pev);

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
string searchDatasheet(const unordered_map<string, string> &dsModels, const int widestModelLength) {
	// TODO: also add some help on this window/form fields using F1
	static const string DATASHEET_HDR("Datasheet ");
	static const string MODEL_HDR("Model ");
	static const string MVP_DISCLAIMER("MVP: UPPERCASE & exact. No autocomplete.");

	const int LINE = 1;
	const int COL = 1;
	const int ML_FIELD_COL = MODEL_HDR.length() + 1;
	const int DS_FIELD_COL = max(static_cast<int>(DATASHEET_HDR.length()) + 1, ML_FIELD_COL + widestModelLength - 7);
	// 7 is fixed; all datasheets are 7 wide
	const int MENU_COL = max(DS_FIELD_COL + 7, ML_FIELD_COL + widestModelLength) + 2;

	static const int WIN_WIDTH = MENU_COL + widestModelLength + 1 + 2 /* border */;
	static const int WIN_HEIGHT = 6 + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Search");

	FormBuilder fb;
	// 7 is fixed; all datasheets are 7 wide
	Field dsField(1, 7, LINE + 0, DS_FIELD_COL);
	dsField.optionAutoSkip(OFF);
	fb.addField(dsField);
	// from database or also hard-coded constant
	Field mdField(1, widestModelLength, LINE + 2, ML_FIELD_COL);
	mdField.optionAutoSkip(OFF);
	fb.addField(mdField);
	SimpleForm form = fb.build<SimpleForm>(center);

	center.add(LINE - 1, COL, MVP_DISCLAIMER);
	center.add(LINE + 0, COL, DATASHEET_HDR);
	center.add(LINE + 2, COL, MODEL_HDR);
	// mock-up, commented for minimum viable product
	// center.add(LINE + 0, MENU_COL - 1, '>');
	// center.add(LINE + 0, MENU_COL, "MSP430F6458");
	// center.add(LINE + 1, MENU_COL, "MSP430F6459");
	// center.add(LINE + 2, MENU_COL, "MSP430F6459-HIREL");

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
