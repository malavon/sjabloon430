#include "ui.hpp"

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;

// 7 is fixed; all datasheets are 7 wide
static const int FIELD_WIDTH_DATASHEET = 7;
// 3 characters is enough for pin numbers, even BGA
// using 4 is however logical, esthetic purposes 1 empty character always
static const int FIELD_WIDTH_PIN = 4;
// packages (drawing + pins) are up to 6 wide, so always format them at 6
static const int FIELD_WIDTH_PKG = 6;
// as far as I know, signal is max 8 EXCEPT for PM_<signal> signals; then it's 11
static const int FIELD_WIDTH_SIGNAL = 11;
static const int FIELD_WIDTH_DESC = 20;

// hard-coded max # of signals required for window size
static const int MAX_SIGNALS = 10;

static const char *SIGNAL_HDR("SIGNAL");
static const char *DESCRIPTION_HDR("DESCRIPTION");

class PinsetView {
	vector<string> pins;
	vector<string> signals;
	vector<string> signalDescs;
};

typedef EventEmittingForm<class PinsetEventer, SimpleFormKeyEventConsumer> PinsetForm;

class PinsetEventer : public FormEventHandler {
  public:
	PinsetEventer(PinsetForm &form, const vector<string> &pkgs, unordered_map<string, string> &signals, int sgnCol) :
		signalColumn(sgnCol), form(form), packages(pkgs), signalAndDescMap(signals) {
		row = 0; // row is locally inside the derived window!
		descColumn = sgnCol + FIELD_WIDTH_SIGNAL + 1;
		// add single set of fields, none exist yet
		addExtraFieldPair();
	}

  private:
	void addExtraFieldPair() {
		Field sgnField(1, FIELD_WIDTH_SIGNAL, row, signalColumn);
		sgnField.justify(JUSTIFY_RIGHT);
		sgnField.optionAutoSkip(Toggle::OFF);
		// test
		// make field required for validation, shouldn't allow leaving the field?
		// result; as-is empty field is allowed, BUT 3 means 2? etc wtf... odd; \0 included?
		// set_field_type(sgnField.raw(), TYPE_ALNUM, 4);
		Field descField(1, FIELD_WIDTH_DESC, row, descColumn);
		descField.optionsActiveAndEditable(Toggle::OFF);
		descField.optionAutoSkip(Toggle::OFF);

		if ( signalAndDescFields.size() % 2 == 1 ) {
			sgnField.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
			descField.setColors(COLOR_PAIR_FORM_SELECTED, COLOR_PAIR_ALTFORM_VALID);
		}

		form.addField(sgnField);
		form.addField(descField);
		signalAndDescFields.push_back(pair<Field, Field>(sgnField, descField));
		previousSignals.push_back("");

		form.repost();
		row++;
	}

	void fieldHopped() {
		int idx = 0;
		bool repost = false;
		bool lastFilledSignalDescEditable = false;

		// if last signal field filled, add pair of fields to form
		// size check just in case
		int signals = signalAndDescFields.size();
		if ( signals > 0 && signals < MAX_SIGNALS ) {
			pair<Field, Field> lastSgn = signalAndDescFields[signalAndDescFields.size() - 1];
			if ( !lastSgn.first.buffer<string>().empty() ) {
				addExtraFieldPair();
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
		}
	}

  public:
	const vector<pair<Field, Field>> &getSignalsVector() const {
		return signalAndDescFields;
	}

	void onNextField() {
		fieldHopped();
	}

	void onPreviousField() {
		fieldHopped();
	}

  private:
	int row;
	// column to use for next signal & desc fields
	int signalColumn, descColumn;
	PinsetForm &form;
	vector<string> packages;
	unordered_map<string, string> signalAndDescMap;

	vector<pair<Field, Field>> signalAndDescFields;
	vector<string> previousSignals;
};

void drawPinSetHeader(Window &win, const int hdrRow, const vector<string> &pkgs) {
	int col = 0;

	col = 0;
	for ( const string &pkg : pkgs ) {
		col += FIELD_WIDTH_PKG + 1;
		int len = pkg.length();
		win.add(hdrRow, col - len, pkg);
	}

	int sgnCol = col + 1;
	int descCol = sgnCol + FIELD_WIDTH_SIGNAL + 1;

	win.add(hdrRow, sgnCol, SIGNAL_HDR);
	win.add(hdrRow, descCol, DESCRIPTION_HDR);
	win.paint();
}

void drawPinSet(Window &win, int &row, const vector<string> &, unordered_map<string, string> &signals, const PinView &pv) {
	int col = 0;
	for ( const string &pin : pv.pins ) {
		col += FIELD_WIDTH_PKG + 1;
		int len = pin.length();
		win.add(row, col - len, pin);
	}

	col++;
	for ( const string &sgn : pv.signals ) {
		win.add(row, col, sgn);
		win.add(row, col + FIELD_WIDTH_SIGNAL + 1, signals[sgn]);
		row++;
	}
}

void editPinSet(Window &win, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, PinView &pv) {
	Window formWin = win.deriveWindow(MAX_SIGNALS, 0, row, 0);

	FormBuilder fb;
	Field *pinFields = new Field[pkgs.size()];

	int col = 0;
	for ( size_t i = 0; i < pkgs.size(); i++ ) {
		col += FIELD_WIDTH_PKG + 1;

		Field fld = Field(1, FIELD_WIDTH_PIN, 0, col - FIELD_WIDTH_PIN);
		fld.justify(JUSTIFY_RIGHT);
		fld.optionAutoSkip(Toggle::OFF);
		fb.addField(fld);
		pinFields[i] = fld;
	}

	PinsetForm form = fb.build<PinsetForm>(formWin);

	int sgnCol = col + 1;
	PinsetEventer pev(form, pkgs, signals, sgnCol);
	form.loop(pev);

	// after looping of edit, complete the pinview
	pv.pins.clear();
	for ( size_t i = 0; i < pkgs.size(); i++ ) {
		pv.pins.push_back(pinFields[i].buffer<string>());
	}

	pv.signals.clear();
	for ( const pair<Field, Field> &sgnAndDesc : pev.getSignalsVector() ) {
		string sgn = sgnAndDesc.first.buffer<string>();
		string desc = sgnAndDesc.second.buffer<string>();
		if ( !sgn.empty() ) {
			pv.signals.push_back(sgn);
			// only allow editing if description is empty?
			// actually, only allow addition?
			if ( signals[sgn].empty() ) {
				signals[sgn] = desc;
			}
		}
	}

	// delete array, DO NOT delete the Fields; they're attached to Form and will be deleted by its destructor
	delete[] pinFields;

	formWin.erase(); // important, erase only the form part of the window
}

// Window drawing functions

// TODO: window should scroll working
void drawPinSetEditingWindow(Window &win, PinSetView &vw) {
	win.erase(); // erase window necessary? erases hotkeys printed in main

	int horizontalLineLength = vw.pkgs.size() * (FIELD_WIDTH_PKG + 1) + FIELD_WIDTH_SIGNAL + FIELD_WIDTH_DESC + 1;
	int row = 0;
	if ( !vw.pinViews.empty() ) {
		drawPinSetHeader(win, row++, vw.pkgs);
	}
	for ( PinView &pv : vw.pinViews ) {
		// drawPinSetHeader(win, row++, vw.pkgs);
		// this line overwrites the header written for edit
		mvwhline(win, row++, 1, 0, horizontalLineLength);
		drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
	}
	mvwhline(win, row++, 1, 0, horizontalLineLength);
	// for now: edit new set at last position
	drawPinSetHeader(win, row++, vw.pkgs); // editing field always gets a header?

	PinView pv;
	editPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
	// TODO: check deletion?

	// only add pin view if at least one pin & one signal
	// to verify: count pin sizes, since the vector itself is not empty!
	int pinTotal = 0;
	for ( auto it = pv.pins.begin(); it != pv.pins.end() && pinTotal == 0; it++ ) {
		pinTotal += it->size();
	}
	if ( pinTotal > 0 && !pv.signals.empty() ) {
		vw.pinViews.push_back(pv);
	}
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
	for ( size_t i = 0; i < packages.size(); i++ ) {
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
