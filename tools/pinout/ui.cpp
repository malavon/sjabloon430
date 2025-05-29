#include "ui.hpp"

#include <cstdio>
#include <set>

namespace sjabloon430 { namespace tools { namespace pinout { namespace ui {

using namespace cccurses;
using namespace sjabloon430::tools::pinout::db;

// internally used (partial window) functions
void drawPinSetHeader(Window &, const int row, const vector<string> &pkgs);
void drawPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &sgn, const db::Signalset &pv);
void editPinSet(Window &, int &row, const vector<string> &pkgs, unordered_map<string, string> &signals, db::Signalset &pv);

// helper functions
// scrolls window if cannot accomodate {rows}, adds amount to currentRow, returns bare amount as well
int scrollToAccomodate(Window &win, int rows, int &currentRow);

// hotkey displays
void displayBrowseHotkeys(Window &);
void displayEditHotkeys(Window &);
// hotkey helpers
void displayHotkey(Window &win, const string &text, const vector<chtype> &keys);
void displayHotkey(Window &win, const string &text, const string &key);

class PinsetEventer : public FormEventHandler {
  public:
	PinsetEventer(Window &win, EventEmittingForm<PinsetEventer> &form, const vector<Package> &pkgs,
		      unordered_map<string, string> &signals, vector<string> initSignals, int sgnCol) :
	    window(win), form(form), packages(pkgs), signalAndDescMap(signals), signalColumn(sgnCol) {
		row = 0; // row is locally inside the derived window!
		descColumn = sgnCol + FIELD_WIDTH_SIGNAL + 1;

		for ( const string &signal : initSignals ) {
			addSignal(signal);
		}
		// add single set of fields, none exist yet
		addExtraFieldPair();
		form.repost();
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

		row++;
	}

	void addSignal(const string signal) {
		addExtraFieldPair();
		pair<Field, Field> pr = *signalAndDescFields.rbegin();
		pr.first.setBuffer(signal);
		string desc = signalAndDescMap[signal];
		pr.second.setBuffer(desc); // assume a description always exists
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
						string description = signalAndDescMap[signalTxt];
						desc.setBuffer(description);
						desc.optionsActiveAndEditable(description.empty() ? Toggle::ON : Toggle::OFF);
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
	const vector<pair<Field, Field>> &getFieldVector() const {
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
	EventEmittingForm<PinsetEventer> &form;
	Window &window;
	vector<Package> packages;
	unordered_map<string, string> signalAndDescMap;

	vector<pair<Field, Field>> signalAndDescFields;
	vector<string> previousSignals;
};

// helper functions
int scrollToAccomodate(Window &win, int rows, int &currentRow) {
	int rowsToScroll = std::max(0, currentRow + rows - win.maxRows());
	if ( rowsToScroll > 0 ) {
		win.scroll(rowsToScroll);
		currentRow -= rowsToScroll;
	}
	return rowsToScroll; // returns how many were scrolled in reality
}

void drawPinSetHeader(Window &win, const int hdrRow, const vector<Package> &pkgs) {
	int col = 0;
	for ( const Package &pkg : pkgs ) {
		col += HEADER_WIDTH_PKG + 1;
		string conc = pkg.drawing + to_string(pkg.pins);
		win.add(hdrRow, col - conc.length(), conc);
	}

	int sgnCol = col + 1;
	int descCol = sgnCol + FIELD_WIDTH_SIGNAL + 1;

	win.add(hdrRow, sgnCol, SIGNAL_HDR);
	win.add(hdrRow, descCol, DESCRIPTION_HDR);
	win.paint();
}

// this function renders a pinset; it assumes that there is enough room available to render 1 signal/line
// +1 line for a horizontal ruler below the last signal
void drawPinSet(Window &win, int &row, const vector<Package> &pkgs, unordered_map<string, string> &signals, const PinView &pv) {
	int col = 0;
	for ( const Package &pkg : pkgs ) {
		col += HEADER_WIDTH_PKG + 1;
		if ( pv.pins.end() == pv.pins.find(pkg) || pv.pins.at(pkg).empty() ) {
			win.add(row, col - 1, '-');
		} else {
			const string pstr = pv.pins.at(pkg); // implicit casting
			win.add(row, col - pstr.length(), pstr);
		}
	}

	col++;
	int descCol = col + FIELD_WIDTH_SIGNAL + 1;
	// cut off descriptions if need be
	int maxDescLength = std::max(FIELD_WIDTH_DESC, win.maxCols() - descCol - 1);
	const string CUT_CHARS = "...";
	for ( const string &sgn : pv[0] ) {
		if ( row < win.maxRows() ) {
			win.add(row, col, sgn);
			if ( signals[sgn].length() > maxDescLength ) {
				win.add(row, descCol, signals[sgn].substr(0, maxDescLength - CUT_CHARS.length()) + CUT_CHARS);
			} else {
				win.add(row, descCol, signals[sgn]);
			}
		}
		row++;
	}
}

// gets data from form and updates signalset AND signals/description data
void formToSignalData(PinView &pv, unordered_map<string, string> &signals, const vector<Package> &pkgs, Field pinFields[],
		      PinsetEventer &pev) {
	for ( int i = 0; i < pkgs.size(); i++ ) {
		// packages have the same ordering as the fields
		string pin = pinFields[i].buffer<string>();
		string::size_type idx = pin.find_first_of("0123456789");
		if ( pin.empty() || idx == string::npos ) { // no legal pin number (always contains a number)
			pv.pins[pkgs[i]] = Pin{};
		} else {
			string bga = (idx == 0) ? "" : pin.substr(0, idx);
			int nr = (idx == 0 ? stoi(pin) : stoi(pin.substr(idx, pin.size())));
			pv.pins[pkgs[i]] = Pin{bga, nr};
		}
	}

	pv[0].clear();
	for ( const pair<Field, Field> &sgnAndDesc : pev.getFieldVector() ) {
		string sgn = sgnAndDesc.first.buffer<string>();
		string desc = sgnAndDesc.second.buffer<string>();
		if ( !sgn.empty() ) {
			pv[0].push_back(sgn);
			if ( signals[sgn].empty() ) {
				signals[sgn] = desc;
			}
		}
	}
}

void editPinSet(Window &win, int &row, const vector<Package> &pkgs, unordered_map<string, string> &signals, PinView &pv) {
	Window formWin = win.deriveWindow(MAX_SIGNALS, 0, row, 0);

	FormBuilder fb;
	Field pinFields[pkgs.size()];

	int col = 0;
	for ( int i = 0; i < pkgs.size(); i++ ) {
		col += HEADER_WIDTH_PKG + 1;

		Field fld = Field(1, FIELD_WIDTH_PIN, 0, col - FIELD_WIDTH_PIN);
		fld.justify(JUSTIFY_RIGHT);
		fld.optionAutoSkip(Toggle::OFF);
		if ( !pv.pins[pkgs[i]].empty() ) {
			fld.setBuffer(pv.pins[pkgs[i]]); // implicit cast to string
		}
		fb.addField(fld);
		pinFields[i] = fld;
	}

	EventEmittingForm<PinsetEventer> form = fb.build<EventEmittingForm<PinsetEventer>>(formWin);

	int sgnCol = col + 1;
	PinsetEventer pev(formWin, form, pkgs, signals, pv[0], sgnCol);

	form.loop(pev);
	formWin.erase(); // important, erase only the form part of the window

	// after looping of edit, complete the pinview
	formToSignalData(pv, signals, pkgs, pinFields, pev);
}

// Window drawing functions

// render all pinviews up to the selected index at least
// MVP: this function keeps the selected index on the last row unless it's on the very first screen
// it might be nicer if it behaves like a text editor: scrollin upwards from below until the first line is reached
void drawPinSetEditingWindow(Window &win, PinSetView &vw) {
	if ( vw.editIdx < 0 ) {
		// erasing window IS necessary to clean everything up BUT ...
		// when editIdx is set, it is set to selIdx meaning everything _can_ simply stay in the same place
		// and the editing form has its own subwindow, which _is_ cleared anyway
		// so no global clear necessary AND the sets below the edited one are still displayed without redrawing!
		win.erase();
	}

	int row = 0, idx = 0;
	bool roomToDisplayMore = true, selectionReached = false;
	for ( vector<PinView>::iterator it = vw.pinViews.begin();
	      it != vw.pinViews.end() && (roomToDisplayMore || !selectionReached); it++, idx++ ) {
		PinView &pv = *it;
		if ( idx == vw.editIdx ) {
			// ensure there is enough room to display entire form, will not be dynamically expanded
			scrollToAccomodate(win, MAX_SIGNALS + 1 /* header */, row);
			drawPinSetHeader(win, row++, vw.pkgs);
			editPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
			row--; // row is restored because this same function call it'll be rendered in THE SAME SPOT

			// if it's not valid, remove it
			if ( !pv.hasPinsAndSignals() ) {
				vw.pinViews.erase(it);
			}

			// if signals are added or removed, everything below will need to be redrawn
			win.clearToEndOfScreen();
		}

		if ( idx == vw.selIdx ) {
			selectionReached = true;
			scrollToAccomodate(win, pv[0].size() + 1 /* header */ + 1 /* horiz. ruler */, row);
			win.enableAttributes(WA_BOLD);
			drawPinSetHeader(win, row++, vw.pkgs);
			for ( int i = 0; i < pv[0].size(); i++ ) {
				win.add(row + i, 1, ">");
			}
			drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
			mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79)); // capped at 80, esthaetics
			win.disableAttributes(WA_BOLD);
		} else if ( !selectionReached ) { // selection not yet reached, keep drawing & scrolling if need be
			int scrolled = scrollToAccomodate(win, pv[0].size() + 1 /* header */ + 1 /* horiz. ruler */, row);
			drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
			mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79)); // capped at 80, esthaetics
			roomToDisplayMore = (scrolled == 0);
		} else if ( roomToDisplayMore ) {    // if there is still some room to render the next signal, do so
			if ( row < win.maxRows() ) { // if there is 1 line available, render partially
				drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
			}
			if ( row < win.maxRows() ) {
				mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79)); // capped at 80, esthaetics
			} else {
				roomToDisplayMore = false;
			}
		}
	}

	// at last option editing means inserting a new one
	if ( vw.editIdx == vw.pinViews.size() ) {
		PinView pv;
		scrollToAccomodate(win, MAX_SIGNALS + 1 /* header */, row);
		drawPinSetHeader(win, row++, vw.pkgs);
		editPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
		// data has been added to given Signalset but is only valid if at least one pin and one signal
		// signals without pins are useless, pins without signals are as well
		row--; // advanced to draw header above, OVERWRITE exact edit position with view-only
		if ( pv.hasPinsAndSignals() ) {
			win.clearLine(row);
			vw.pinViews.push_back(pv);
			drawPinSet(win, row, vw.pkgs, vw.signalDescs, pv);
			mvwhline(win, row++, 1, 0, min(win.maxCols() - 2, 79)); // capped at 80, esthaetics
			vw.selIdx++;
		}
	}

	// scrolled/selected all the way to the botton
	// render an empty placeholder
	if ( vw.selIdx == vw.pinViews.size() ) {
		scrollToAccomodate(win, 2, row);
		win.enableAttributes(WA_BOLD);
		drawPinSetHeader(win, row++, vw.pkgs);
		win.add(row++, 1, "> End of signals reached. Inserting will add a new signalset.");
		win.disableAttributes(WA_BOLD);
	}
}

void drawSetConfigWindow(BorderedWindow &win, const vector<db::Orderable> odbls) {
	win.clear();
	std::set<string> models;
	std::set<Package> pkgs;
	for ( const Orderable &o : odbls ) {
		models.insert(o.model);
		pkgs.insert(o.pkg);
	}
	drawSetConfigWindow(win, vector<string>(models.begin(), models.end()), vector<Package>(pkgs.begin(), pkgs.end()));
}

void drawSetConfigWindow(BorderedWindow &win, const vector<string> &models, const vector<Package> &pkgs) {
	const int MAX_PKG_LEN = 6;
	const int COL_HDR = 1;
	const int COL_DATA = 2;

	int lr = 0;
	win.add(lr++, COL_HDR, "Models:");
	for ( const string &model : models ) {
		win.add(lr++, COL_DATA, model);
	}

	win.add(lr++, COL_HDR, "Packages:");
	for ( int i = 0; i < pkgs.size(); i++ ) {
		const string pkg = pkgs[i].drawing + to_string(pkgs[i].pins);
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
	if ( win.maxCols() >= fullHdr.length() + 2 ) {
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
		if ( win.maxCols() >= shortHdr.length() + 2 ) {
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

void loopPinsetEditing(Window &win, Window &hot, BorderedWindow &config, ui::PinSetView &vw, vector<db::Orderable> &ordbls) {
	int tempChar = 0;
	do {
		switch ( tempChar ) {
			case KEY_UP:
				vw.selIdx = max(0, vw.selIdx - 1);
				break;
			case KEY_DOWN:
				// size() is 1 higher than max to allow selecting pin at the end
				vw.selIdx = min(static_cast<int>(vw.pinViews.size()), vw.selIdx + 1);
				break;
			case KEY_ENTER:
			case 10 /* RETURN */:
				vw.editIdx = vw.selIdx;
				displayEditHotkeys(hot);
				break;
			case KEY_IC /* insert */:
				// insert and edit; will be removed by ui code if no signals are inserted!
				if ( vw.selIdx < vw.pinViews.size() ) {
					vw.pinViews.insert(vw.pinViews.begin() + vw.selIdx, PinView());
					vw.editIdx = vw.selIdx;
				}
				break;
			case KEY_DC /* delete */:
				if ( vw.selIdx < vw.pinViews.size() ) {
					vw.pinViews.erase(vw.pinViews.begin() + vw.selIdx);
				}
				break;
			case KEY_F(5):
			case KEY_F(6):
			case KEY_F(7): {
				std::set<string> models;
				std::set<Package> pkgs;
				for ( const db::Orderable &o : ordbls ) {
					models.insert(o.model);
					pkgs.insert(o.pkg);
				}
				vector<string> mv(models.begin(), models.end());
				vector<Package> pv(pkgs.begin(), pkgs.end());
				vector<db::Orderable> newo = ui::filterForConfigset(pv, mv, ordbls);
				ui::drawSetConfigWindow(config, newo);
			} break;
			case 27 /*ESCAPE*/: // open a menu or something, probably beyond MVP though
				break;
		}

		drawPinSetEditingWindow(win, vw);
		displayBrowseHotkeys(hot); // default hotkeys
		vw.editIdx = -1;	   // reset editIdx otherwise editing would never stop
	} while ( (tempChar = wgetch(win)) != 27 ); // ESC key for exit
}

// used to create config set, display packages & devices for the user to filter them
vector<db::Orderable> filterForConfigset(const vector<Package> &ps, const vector<string> &ms, const vector<db::Orderable> &os) {
	static const string TEXT = "Select devices OR packages to use for the set.";
	static const string KEYS = "U/D Move TAB/STAB Models/Packages SPACE Select RETURN Confirm"; // marker for length
	static const int TEXT_WIDTH = max(TEXT.length(), KEYS.length());

	int WIN_WIDTH = max(TEXT_WIDTH, max(HEADER_WIDTH_PKG + 1, 18)) + 2 /* Whitespace Left/right  */ + 2 /* border */;
	int WIN_HEIGHT = std::max(ps.size(), ms.size()) + 3 /* text & empty line */ + 1 /* empty line */ + 2 /* border */;

	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Filter");
	center.add(0, (center.maxCols() - TEXT.length()) / 2 - 1, TEXT);
	center.moveCursor(1, (center.maxCols() - KEYS.length()) / 2 - 1);
	displayHotkey(center, "Move", vector<chtype>{ACS_UARROW, '/', ACS_DARROW});
	displayHotkey(center, "Models/Packages", "TAB/STAB");
	displayHotkey(center, "Select", "SPACE");
	displayHotkey(center, "Confirm", "RETURN");
	center.paint();

	enum { MODELS = 0, PACKAGES = 1 };
	// using arrays for these greatly simplifies below code
	// of course, using some sort of selection box would do this even more :)
	unsigned int selIdx[2] = {0, 0},
		     maxIdx[] = {static_cast<unsigned int>(ms.size() - 1), static_cast<unsigned int>(ps.size() - 1)};
	int intIdx = MODELS; // working with index creates shortest code
	// selection masks; using entire int-space; 15 models is maximum in database though
	// this is the clever bit ... right?
	int bitMsks[] = {-1, -1};

	int pressedKey = 0;
	do {
		switch ( pressedKey ) {
			case 9 /* tab */:
			case KEY_BTAB:
				intIdx = intIdx == MODELS ? PACKAGES : MODELS;
				break;
			case KEY_UP:
				selIdx[intIdx] = selIdx[intIdx] > 0 ? selIdx[intIdx] - 1 : maxIdx[intIdx];
				break;
			case KEY_DOWN:
				selIdx[intIdx] = selIdx[intIdx] < maxIdx[intIdx] ? selIdx[intIdx] + 1 : 0;
				break;
			case ' ':
				bitMsks[intIdx] ^= 1 << selIdx[intIdx];
				break;
		}

		int colMdl = 4;
		int colPkg = center.maxCols() - HEADER_WIDTH_PKG - 4 - 4;
		int row = 3;
		for ( int i = 0; i < ms.size(); i++ ) {
			center.add(row + i, colMdl, bitMsks[0] & (1 << i) ? " [X] " : " [ ] ");
			center.add(ms[i], i == selIdx[0] && intIdx == 0 ? A_STANDOUT : A_NORMAL);
		}
		for ( int i = 0; i < ps.size(); i++ ) {
			center.add(row + i, colPkg, ps[i], i == selIdx[1] && intIdx == 1 ? A_STANDOUT : A_NORMAL);
			center.add(row + i, colPkg + HEADER_WIDTH_PKG, bitMsks[1] & (1 << i) ? "[X] " : "[ ] ");
		}

		// naive way of moving cursor where it doesn't bother as much, should hide it somehow TODO
		center.moveCursor(center.maxRows() - 1, center.maxCols() - 1);
		center.paint();
	} while ( (pressedKey = wgetch(center)) != KEY_ENTER && pressedKey != 10 );

	vector<db::Orderable> fltrd;
	for ( const db::Orderable &o : os ) {
		int mdlIdx = 0, pkgIdx = 0;
		// there is no find/search with indices in C++? :'(
		// can maybe solved with one of the newer std::* thingies
		for ( vector<string>::const_iterator it = ms.begin(); it < ms.end() && *it != o.model; it++, mdlIdx++ ) { }
		for ( vector<Package>::const_iterator it = ps.cbegin(); it < ps.end() && *it != o.pkg; it++, pkgIdx++ ) { }

		// asserts will never hit if models/packages/orderables are correctly retrieved from the DB
		assert(mdlIdx < ms.size());
		assert(pkgIdx < ps.size());

		if ( bitMsks[MODELS] & (1 << mdlIdx) && bitMsks[PACKAGES] & (1 << pkgIdx) ) {
			fltrd.push_back(o);
		}
	}
	return fltrd;
}

// reordering packages, given vector is reordered
void reorderPackages(vector<Package> &pkgs) {
	static const string TEXT = "Reorder packages as they are in the datasheet";
	static const string KEYS = "TAB/STAB Select L/R Move Enter/Return Confirm"; // only here for calculations
	static const int TEXT_WIDTH = max(TEXT.length(), KEYS.length());

	int PKGS_WIDTH = pkgs.size() * (HEADER_WIDTH_PKG + 1) - 1;

	int WIN_WIDTH = max(TEXT_WIDTH, PKGS_WIDTH) + 2 /* Whitespace Left/right  */ + 2 /* border */;
	int WIN_HEIGHT = 3 /* text & empty line */ + 1 /* line with packages */ + 1 /* empty line */ + 2 /* border */;

	// TODO: doesn't care about resizing or too small a screen
	BorderedWindow center(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2, (COLS - WIN_WIDTH) / 2);
	center.setTitle("Ordering");
	center.add(0, (center.maxCols() - TEXT.length()) / 2, TEXT);
	center.moveCursor(1, (center.maxCols() - KEYS.length()) / 2 - 1);
	displayHotkey(center, "Select", "TAB/STAB");
	displayHotkey(center, "Move", vector<chtype>{ACS_LARROW, '/', ACS_RARROW});
	displayHotkey(center, "Confirm", "Enter/Return");

	int totalPkgsLength = -1;
	for ( const Package &pkg : pkgs ) {
		totalPkgsLength += pkg.drawing.length() + to_string(pkg.pins).length() + 1;
	}

	center.paint();

	// simple manual key detection
	// cccurses should have a good way to capture these without checking key codes etc
	// current KeyEventProducer might be too much for this purpose? should try it out really
	int slIdx = 0;
	int maxIdx = pkgs.size() - 1;
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
					pkgs[--slIdx] = temp; // hehe²
				}
				break;
			case KEY_RIGHT:
				if ( slIdx < maxIdx ) {
					Package temp = pkgs[slIdx];
					pkgs[slIdx] = pkgs[slIdx + 1];
					pkgs[++slIdx] = temp; // hehe²
				}
				break;
		}

		int col = (WIN_WIDTH - 4 - totalPkgsLength) / 2;
		center.clearLine(3);
		for ( int i = 0; i < pkgs.size(); i++ ) {
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

// hotkey helpers
void displayHotkey(Window &win, const string &text, const vector<chtype> &keys) {
	win.add(' ');
	for ( const chtype key : keys ) {
		win.add(key | A_STANDOUT);
	}
	win.add(' ');
	win.add(text);
}

void displayHotkey(Window &win, const string &text, const string &key) {
	win.add(' ');
	win.add(key, A_STANDOUT);
	win.add(' ');
	win.add(text);
}

void displayBrowseHotkeys(Window &win) {
	win.clearLine(0);
	displayHotkey(win, "QUIT", "ESC");
	displayHotkey(win, "Nav.", vector<chtype>({ACS_UARROW, '/', ACS_DARROW}));
	displayHotkey(win, "Edit", "Enter");
	displayHotkey(win, "Insert", "Ins");
	displayHotkey(win, "Delete", "Del");
	win.paint();
}

void displayEditHotkeys(Window &win) {
	win.clearLine(0);
	displayHotkey(win, "Nav.", "TAB/STAB");
	displayHotkey(win, "Confirm", "Enter");
	win.paint();
}

}}}} // namespace sjabloon430::tools::pinout::ui
