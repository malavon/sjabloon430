#include "ui.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

class PinsetEventer : public FormEventHandler {
  public:
	PinsetEventer(EventEmittingForm<PinsetEventer> &form, unordered_map<string, string> &signals, int signalColumn,
		      int descColumn) :
	    form(form), signalAndDescMap(signals), signalColumn(signalColumn), descColumn(descColumn) { }

  private:
	void fieldHopped() {
		int idx = 0;
		bool repost = false;
		bool lastFilledSignalDescEditable = false;

		// if last signal field filled, add pair of fields to form
		// size check just in case
		int signals = signalAndDescFields.size();
		if ( signals > 0 && signals < 9 /* hard-coded based on window size of 10 ... */ ) {
			pair<Field, Field> lastSgn = signalAndDescFields[signalAndDescFields.size() - 1];
			if ( !lastSgn.first.buffer<string>().empty() ) {
				// TODO: constant usage etc for location
				int nextLine = signals + 1;
				Field sgnField(1, 8, nextLine, signalColumn);
				sgnField.justify(JUSTIFY_RIGHT);
				Field descField(1, 20, nextLine, descColumn);
				descField.optionsActiveAndEditable(Toggle::OFF);
				if ( signals % 2 == 1 ) {
					sgnField.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
					descField.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
				}

				// TODO: adding form.addField calls to addFields doesn't work? :(
				form.addField(sgnField);
				form.addField(descField);
				addFields(sgnField, descField);
				repost = true;
			}
		}

		// all fields: if changed, check signal and set desc (un-)editable or
		for ( pair<Field, Field> &pr : signalAndDescFields ) {
			Field &sgn = pr.first;
			Field &desc = pr.second;

			string signalTxt = sgn.buffer<string>();
			// only do anything IF the signal has changed
			if ( signalTxt != previousSignals[idx] ) {
				// this way it is set to false UNLESS the very last iteration sets it to true
				lastFilledSignalDescEditable = false;

				previousSignals[idx] = signalTxt;
				repost = true;
				// no description for empty signal, but not editable either
				if ( signalTxt.empty() ) {
					desc.optionsActiveAndEditable(Toggle::OFF);
				} else {
					if ( signalAndDescMap.find(signalTxt) == signalAndDescMap.end() ) {
						desc.optionsActiveAndEditable(Toggle::ON);
						lastFilledSignalDescEditable = true;
						// also: required (todo: also in other branches)
					} else {
						// exists
						desc.optionsActiveAndEditable(Toggle::OFF);
						string description = signalAndDescMap[signalTxt];
						// todo: implement on field
						desc.setBuffer(description);
					}
				}
			}
			idx++;
		}

		if ( repost ) {
			form.repost();
			// using form_driver directly for now
			// there are limited options, most logically a certain field should be focused
			// instead of last or last by one field
			// last field is the (empty) signal field
			// last - 1 is the description field of the last filled signal
			form_driver(form, REQ_LAST_FIELD);
			if ( lastFilledSignalDescEditable ) {
				form_driver(form, REQ_PREV_FIELD);
			}

			// TODO: redraw?
		}
	}

  public:
	void onNextField() {
		fieldHopped();
	}

	void onPreviousField() {
		fieldHopped();
	}

	void addFields(const Field &signalField, const Field &descField) {
		signalAndDescFields.push_back(pair<Field, Field>(signalField, descField));
		previousSignals.push_back(signalField.buffer<string>());
	}

  private:
	// column to use for next signal & desc fields
	int signalColumn, descColumn;
	EventEmittingForm<PinsetEventer> &form;
	unordered_map<string, string> signalAndDescMap;
	vector<pair<Field, Field>> signalAndDescFields;
	vector<string> previousSignals;
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
	descField.optionsActiveAndEditable(Toggle::OFF);
	fb.addField(descField);

	// is there a benefit of creating this derived/subwindow for the form?
	// clear on one is clear on the other ... useless?
	// 10 - pinRow signals are maximum; above that repost() will result in assertion!!! CRASH
	// also: draw of all pins should probably start after subwindow then? less redrawing
	Window formWin = win.deriveWindow(10, 0, 1, 0);
	EventEmittingForm<PinsetEventer> form = fb.build<EventEmittingForm<PinsetEventer>>(formWin);

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

	// eventer knows form to add fields
	unordered_map<string, string> map; // TODO
	map["TEST"] = "TEST SIGNAL DESC";
	PinsetEventer pev(form, map, sgnCol, descCol);
	pev.addFields(sgnField, descField);

	form.loop(pev);

	// TODO: check deletion
}

void drawSetConfigWindow(BorderedWindow &win, const vector<string> &models, const vector<string> &packages) {
	const int MAX_PKG_LEN = 6;
	const int COL_HDR = 1;
	const int COL_DATA = 2;

	int lr = 0;
	win.add(lr++, COL_HDR, "Models:");
	for ( const string &model : models ) {
		win.add(lr++, COL_DATA, model);
	}

	win.add(lr++, COL_HDR, "Packages:");
	for ( int i = 0; i < packages.size(); i++ ) {
		string pkg = packages[i];
		if ( i % 2 == 0 ) {
			win.add(lr, COL_DATA, pkg);
		} else {
			win.add(lr, COL_DATA + MAX_PKG_LEN + 1 + (MAX_PKG_LEN - pkg.length()), pkg);
			lr++;
		}
	}

	win.paint();
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
	dsField.optionAutoSkip(Toggle::OFF);
	fb.addField(dsField);
	// from database or also hard-coded constant
	Field mdField(1, widestModelLength, LINE + 2, ML_FIELD_COL);
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
