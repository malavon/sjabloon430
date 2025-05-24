#include "ui.hpp"

#include <cstdio>

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::pinout::db;

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
	PinsetEventer(Window &win, PinsetForm &form, const vector<Package> &pkgs, unordered_map<string, string> &signals,
			  int sgnCol) : signalColumn(sgnCol), form(form), window(win), packages(pkgs), signalAndDescMap(signals) {
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

		// calculate description field to reach column 80, with a sensible minimum width
		// but ensure that the window can fit it (although application requires 80 cols minimum)
		int descFieldWidth = max(FIELD_WIDTH_DESC, min(80, window.size().cols) - descColumn - 1);

		Field descField(1, descFieldWidth, row, descColumn);
		descField.optionsActiveAndEditable(Toggle::OFF);
		descField.optionAutoSkip(Toggle::OFF);
		descField.makeDynamic(0); // make it dynamic without size restriction; trust the user ...

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
	Window &window;
	vector<Package> packages;
	unordered_map<string, string> signalAndDescMap;

	vector<pair<Field, Field>> signalAndDescFields;
	vector<string> previousSignals;
};

void drawPinSetHeader(Window &win, const int hdrRow, const vector<Package> &pkgs) {
	int col = 0;

	col = 0;
	for ( const Package &pkg : pkgs ) {
		col += FIELD_WIDTH_PKG + 1;
		string conc = pkg.drawing + to_string(pkg.pins);
		win.add(hdrRow, col - conc.length(), conc);
	}

	int sgnCol = col + 1;
	int descCol = sgnCol + FIELD_WIDTH_SIGNAL + 1;

	win.add(hdrRow, sgnCol, SIGNAL_HDR);
	win.add(hdrRow, descCol, DESCRIPTION_HDR);
	win.paint();
}

void drawPinSet(Window &win, int &row, const vector<Package> &pkgs, unordered_map<string, string> &signals, const PinView &pv) {
	unsigned int maxRows = win.maxRows();
	if ( row + std::max(3ul /*always 1 line; 2?3?*/, pv[0].size()) > maxRows ) {
		int rowsToScroll = row + 1 + pv[0].size() - maxRows;
		win.scroll(rowsToScroll);
		row -= rowsToScroll;
	}

	mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79)); // capped at 80, esthaetics
	int col = 0;
	for ( const Package &pkg : pkgs ) {
		col += FIELD_WIDTH_PKG + 1;
		const Pin pin = pv.pins.at(pkg);
		const string pstr = pin.bgaRow + to_string(pin.number);
		win.add(row, col - pstr.length(), pstr);
	}

	col++;
	int descCol = col + FIELD_WIDTH_SIGNAL + 1;
	// cut off descriptions if need be
	size_t maxDescLength = std::max(FIELD_WIDTH_DESC, win.size().cols - descCol - 1);
	const string CUT_CHARS = "...";
	for ( const string &sgn : pv[0] ) {
		win.add(row, col, sgn);
		if ( signals[sgn].length() > maxDescLength ) {
			win.add(row, descCol, signals[sgn].substr(0, maxDescLength - CUT_CHARS.length()) + CUT_CHARS);
		} else {
			win.add(row, descCol, signals[sgn]);
		}
		row++;
	}
}

void editPinSet(Window &win, int &row, const vector<Package> &pkgs, unordered_map<string, string> &signals, PinView &pv) {
	// calculate to allow enough lines to print line, header & form
	int maxRows = win.maxRows();
	if ( row + 2 + MAX_SIGNALS > maxRows ) {
		int rowsToScroll = row + 2 + MAX_SIGNALS - maxRows;
		win.scroll(rowsToScroll);
		row -= rowsToScroll;
	}

	if ( maxRows > 16 ) { // don't print the ruler if the lines are really, really compressed
		mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79));
	}
	// editing field always gets a header, unless there is no room for it
	if ( maxRows > MAX_SIGNALS ) {
		drawPinSetHeader(win, row++, pkgs);
	}

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
	PinsetEventer pev(formWin, form, pkgs, signals, sgnCol);

	form.loop(pev);

	// after looping of edit, complete the pinview
	for ( size_t i = 0; i < pkgs.size(); i++ ) {
		// packages have the same ordering as the fields
		string pin = pinFields[i].buffer<string>();
		if ( pin.empty() ) {
			pv.pins[pkgs[i]] = Pin{};
		} else {
			string::size_type idx = pin.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
			string bga = (idx == string::npos) ? "" : pin.substr(0, idx + 1);
			int nr = (idx == string::npos) ? stoi(pin) : stoi(pin.substr(idx + 1, pin.size()));
			pv.pins[pkgs[i]] = Pin{bga, nr};
		}
	}

	pv.cview.signals.clear();
	for ( const pair<Field, Field> &sgnAndDesc : pev.getSignalsVector() ) {
		string sgn = sgnAndDesc.first.buffer<string>();
		string desc = sgnAndDesc.second.buffer<string>();
		if ( !sgn.empty() ) {
			pv.cview.signals.push_back(sgn);
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

	int row = 0;
	if ( !vw.pinViews.empty() ) {
		drawPinSetHeader(win, row++, vw.pkgs);
	}
	for ( PinView &pv : vw.pinViews ) {
		// drawPinSetHeader(win, row++, vw.pkgs);
		// this line overwrites the header written for edit
		drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
	}

	PinView pv;
	editPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
	// TODO: check deletion?

	// only add pin view if at least one pin & one signal
	// to verify: count pin (string) length, since the map itself is not empty!
	int pinTotal = 0;
	for ( auto it = pv.pins.begin(); it != pv.pins.end() && pinTotal == 0; it++ ) {
		Pin pin = it->second;
		string pstr = pin.bgaRow + to_string(pin.number);
		pinTotal += pstr.length();
	}
	if ( pinTotal > 0 && !pv[0].empty() ) {
		vw.pinViews.push_back(pv);
	}
}

void drawSetConfigWindow(BorderedWindow &win, const vector<string> &models, const vector<Package> &packages) {
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
		const string pkg = packages[i].drawing + to_string(packages[i].pins);
		if ( i % 2 == 0 ) {
			win.add(lr, COL_DATA, pkg);
		} else {
			win.add(lr, COL_DATA + MAX_PKG_LEN + 1 + (MAX_PKG_LEN - pkg.length()), pkg);
			lr++;
		}
	}

	win.paint();
}

void drawTopWindow(BorderedWindow &win, const Datasheet &ds, const DatabaseTotals &ttl, const DatabaseTotals &sprt) {
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

	static const int BFR = 64;
	char buffer[BFR] = "";
	string fullHdr = "DB supported/total (%): ";
	std::snprintf(buffer, BFR, "%d/%d datasheets (%#.1f%%)", sprt.datasheets, ttl.datasheets,
		      100.0f * sprt.datasheets / ttl.datasheets);
	fullHdr += buffer;
	std::snprintf(buffer, BFR, ", %d/%d devices (%#.1f%%)", sprt.devices, ttl.devices, 100.0f * sprt.devices / ttl.devices);
	fullHdr += buffer;
	std::snprintf(buffer, BFR, " and %d/%d orderables (%#.1f%%)", sprt.orderables, ttl.orderables,
		      100.0f * sprt.orderables / ttl.orderables);
	fullHdr += buffer;
	if ( win.maxCols() >= static_cast<int>(fullHdr.length()) + 2 ) {
		win.add(topLine + 2, topCol, fullHdr);
	} else {
		string shortHdr = "DB (sprt/ttl/%):";
		std::snprintf(buffer, BFR, " %d/%d sheets (%#.1f%%)", sprt.datasheets, ttl.datasheets,
			      100.0f * sprt.datasheets / ttl.datasheets);
		shortHdr += buffer;
		std::snprintf(buffer, BFR, ", %d/%d devs (%#.1f%%)", sprt.devices, ttl.devices,
			      100.0f * sprt.devices / ttl.devices);
		shortHdr += buffer;
		std::snprintf(buffer, BFR, ", %d/%d ordbls (%#.1f%%)", sprt.orderables, ttl.orderables,
			      100.0f * sprt.orderables / ttl.orderables);
		shortHdr += buffer;
		if ( win.maxCols() >= static_cast<int>(shortHdr.length()) + 2 ) {
			win.add(topLine + 2, topCol, shortHdr);
		} else {
			win.add(topLine + 2, topCol, "DB:");
			win.print(" %d/%d DS", sprt.datasheets, ttl.datasheets);
			win.print(", %d/%d DEV", sprt.devices, ttl.devices);
			win.print(", %d/%d ODBL", sprt.orderables, ttl.orderables);
		}
	}
	win.paint();
}

// reordering packages, given vector is reordered
void reorderPackages(vector<Package> &pkgs) {
	static const string TEXT = "Reorder packages as they are in the datasheet";
	static const string KEYS = "TAB: Select | Arrow Left/Right: Move | Enter: Confirm";
	static const int TEXT_WIDTH = max(TEXT.length(), KEYS.length());

	int PKGS_WIDTH = pkgs.size() * (FIELD_WIDTH_PKG + 1) - 1;

	int WIN_WIDTH = max(TEXT_WIDTH, PKGS_WIDTH) + 2 /* Whitespace Left/right  */ + 2 /* border */;
	int WIN_HEIGHT = 3 /* text & empty line */ + 1 /* line with packages */ + 1 /* empty line */ + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Ordering");
	center.add(0, (WIN_WIDTH - TEXT.length()) / 2 - 1, TEXT);
	center.add(1, (WIN_WIDTH - KEYS.length()) / 2 - 1, KEYS);

	int totalPkgsLength = -1;
	for ( const Package &pkg : pkgs ) {
		totalPkgsLength += pkg.drawing.length() + to_string(pkg.pins).length() + 1;
	}

	center.paint();

	// simple manual key detection
	// cccurses should have a good way to capture these without checking key codes etc
	// current KeyEventProducer might be too much for this purpose? should try it out really
	size_t slIdx = 0;
	size_t maxIdx = pkgs.size() - 1;
	int pressedKey = 0;
	do {
		switch ( pressedKey ) {
			case 9 /* tab */:
				// allow rollover during selection
				slIdx = (slIdx == maxIdx) ? 0 : slIdx + 1;
				break;
			case KEY_BTAB:
				slIdx = (slIdx == 0) ? maxIdx : slIdx - 1;
				break;
			case KEY_LEFT:
				// no roll-over during move
				if ( slIdx > 0 ) {
					Package temp = pkgs[slIdx];
					pkgs[slIdx] = pkgs[slIdx - 1];
					pkgs[--slIdx] = temp; // hehe
				}
				break;
			case KEY_RIGHT:
				if ( slIdx < maxIdx ) {
					Package temp = pkgs[slIdx];
					pkgs[slIdx] = pkgs[slIdx + 1];
					pkgs[++slIdx] = temp; // hehe
				}
				break;
		}

		int col = (WIN_WIDTH - 4 - totalPkgsLength) / 2;
		center.clearLine(3);
		for ( size_t i = 0; i < pkgs.size(); i++ ) {
			const string pkg = pkgs[i].drawing + to_string(pkgs[i].pins);
			center.add(3, col, pkg, i == slIdx ? A_STANDOUT : A_NORMAL);
			col += pkg.length() + 1;
		}

		// naive way of moving cursor where it doesn't bother as much, should hide it somehow TODO
		center.moveCursor(WIN_HEIGHT - 3, WIN_WIDTH - 3);
		center.paint();
	} while ( (pressedKey = wgetch(center)) != KEY_ENTER && pressedKey != 10 );
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
