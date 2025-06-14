
#include <iostream>
#include <set>

#include "database-files.hpp"
#include "database.hpp"
#include "ui.hpp"
#include "cccurses/cccurses.hpp"
#include "cccurses/form.hpp"
#include "cccurses/window.hpp"

using namespace cccurses;
using namespace sjabloon430::tools::pinout;
namespace dbf = sjabloon430::tools::db;
using sjabloon430::tools::Package;
using sjabloon430::tools::Pin;

void convertDbToView(const vector<db::Signalset> &, vector<db::Pinset> &, vector<db::Orderable> &, ui::PinSetView &);
void convertAndSaveViewToDb(sqlite3 *db, ui::PinSetView &);

static const int WIDEST_MODEL_LENGTH = strlen("MSP430F6459-HIREL"); /* hardcoded longest model */
static const int WIN_TOP_HEIGHT = 6;
static const int WIN_CONFIGSET_WIDTH = WIDEST_MODEL_LENGTH + 2 /* indent */ + 2 /* borders */;

static const int ROW_HOTKEYS = WIN_TOP_HEIGHT - 2 /* borders*/ - 1 /* last line */;

int main() {
	setlocale(LC_ALL, "");

	// SQLite3 in-memory DB
	sqlite3 *db = db::createDatabase();
	if ( db == nullptr ) {
		exit(-1);
	}
	// importing database happens after curses setup, showing which files are read

	/* Initialize curses */
	initCurses();

	{
		BorderedWindow top(WIN_TOP_HEIGHT, COLS - WIN_CONFIGSET_WIDTH, 0, 0);
		// TODO: no border, separate with hline or something?
		Window hotkeys = top.deriveWindow<Window>(1, top.maxCols(), ROW_HOTKEYS, 0);
		Window pins(LINES - WIN_TOP_HEIGHT, COLS - WIN_CONFIGSET_WIDTH, WIN_TOP_HEIGHT, 0);
		pins.optionScrollable(Toggle::ON);
		BorderedWindow configs(LINES, WIN_CONFIGSET_WIDTH, 0, COLS - WIN_CONFIGSET_WIDTH);
		configs.setTitle("Configsets");

		Window &statusWin = pins;
		statusWin.add(0, 0, "Imported SQLite DB from files:\n");
		dbf::importDatabase(db, [&](const string &filename, const char *error) {
			statusWin.add("   \"");
			statusWin.add(filename);
			statusWin.add('"');

			if ( error != nullptr ) {
				statusWin.add(" ERR: ");
				statusWin.add(error);
			}
			statusWin.add('\n'); // scrolls if too many lines for window without possibly erroring
		});
		statusWin.paint();

		// initial state: open search window
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST_MODEL_LENGTH);
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);

		db::DatabaseTotals totals = db::countTotals(db);
		db::DatabaseTotals supported = db::countSupported(db);

		ui::drawTopWindow(top, selectedDS, totals, supported);

		vector<string> models = db::findModelsByDatasheet(db, selectedId);
		// models are used for (default) set
		// TODO: other sets have to be retrieved from pinset & calculated

		vector<Package> pkgs = db::findPackagesByDatasheet(db, selectedDS.id);
		// packages are also used for sets

		// /signalsets/pinsets are also linked to orderables and thus model/package
		vector<db::Signalset> signalsets = db::findSignalsetsByDatasheet(db, selectedId);
		// does not yet use config sets, but this is where the logic could go
		vector<db::Pinset> pinsets = db::findPinsetsByDatasheet(db, selectedId, signalsets);
		// orderables are used to create config sets (the thing at the right :p) -> but not yet implemented
		vector<db::Orderable> ordbls = db::findOrderablesByDatasheet(db, selectedId, pinsets);

		ui::reorderPackages(pkgs);
		ui::PinSetView vw{pkgs};
		vw.signalDescs = db::listAllSignalDescriptions(db);
		convertDbToView(signalsets, pinsets, ordbls, vw);

		ui::loopPinsetEditing(pins, hotkeys, configs, vw);

		db::saveSignals(db, vw.signalDescs);
		dbf::exportSignals(db);

		convertAndSaveViewToDb(db, vw);

		dbf::exportDataForDatasheet(db, selectedId);
		// it would make sense that these are removed and all dev's and odbls are in files per datasheet ...
		dbf::exportDevicesWithoutPinout(db);
		dbf::exportOrderablesWithoutPinout(db);

		// TODO: input up/down & other hotkeys, basically the bulk of the application?
		// or should this be in the main application?
		// much more logical I think, since DB access is required for saving

		// TODO: save new signals; allow changes to descs? maybe, maybe not? better manually?

		// next step would be: get pinset, render to screen
		// BUT: there are no pinsets in DB yet, so first thing is to add creation/editing code
		/* MVP sequence:
		 * 1. get packages & pins for datasheet, get models (models from vector? more difficult)
		 * 1a. user orders packages according to datasheet
		 * 2. print header (assume all packages are added in one go, type 1 datasheets)
		 * 3. add form for pins under each package + 1 signal, on signal field 1 tab:
		 * 3a. lookup signal (none in DB yet), show description
		 * 3b. if description empty: add REQUIRED field // TODO: form extension? unpost/post? tab focuses
		 * 3c. tab: create new signal field
		 * 3d. tab: if next signal field filled, go to 3b, otherwise 4
		 * 4. add new pin, go to 3 (or 2? maybe every X pins?)
		 */
		/* MVP+1:
		 * uppercase input only?
		 * V1.0
		 * autocomplete signals from DB
		 */
	}

	endCurses();

	return EXIT_SUCCESS;
}

// Starting from pinsets is not possible BUT not every pinset is linked through orderable (i.e. parent pinsets).
// On top this also improves support for save-and-pick-up-later editing.
// logic: * all pinsets without parents are part of the default config set
//	  * all pinsets that have default pinsets as parent, are the second config set
//	  * all pinsets that have second ... etc
// Note: - pinsets are (required to be) ordered by id & parent id, so parents always come before their children!
//	 - every pinset already has a valid DB id since the data is supposed to be coming straight from DB!
void pinsetsToViewConfigsets(const vector<db::Pinset> &psv, ui::PinSetView &vw, unordered_map<int, int> &id2cs,
			     set<int> pids = {0}) {
	int lastPnt = 0;
	if ( !pids.empty() ) {
		set<int> nextPids;
		for ( const db::Pinset &ps : psv ) {
			if ( pids.find(ps.parentId) != pids.end() ) {
				// parents should be incrementing WITHIN the same set, start a new set when this isn't true
				if ( lastPnt != 0 && ps.parentId <= lastPnt ) {
					pinsetsToViewConfigsets(psv, vw, id2cs, nextPids);
					nextPids.clear();
					ui::Configset cs;
					vw.add(cs);
				}

				nextPids.insert(ps.id);
				id2cs[ps.id] = vw.csets.size();
				lastPnt = ps.parentId;
			}
		}
		// if this assert hits, there are 2 configsets with the same parent ... which indicates DB inconsistency
		assert(nextPids.size() <= vw.pkgs.size());
		if ( !nextPids.empty() ) { // only add if some pinsets where processed
			ui::Configset cs;
			vw.add(cs);

			// forcibly remove parent ids to ensure there are no loops (on consecutive levels)
			// id can be 0 WHEN orderable has NO pinset linked yet; 0 signifies NULL -> WILL create a loop
			for ( int pid : pids ) {
				nextPids.erase(pid);
			}
			pinsetsToViewConfigsets(psv, vw, id2cs, nextPids);
		}
	}
}

/* REQUIRES:
 * - pinsets sorted by pinset id ascending
 * - orderables sorted by PINSET ID ascending!
 */
void convertDbToView(const vector<db::Signalset> &ssv, vector<db::Pinset> &psv, vector<db::Orderable> &odv,
		     ui::PinSetView &vw) {
	// quick return in case there are no pinsets, thus no pinsets/signalsets etc: add default configset
	if ( psv.size() == 0 ) {
		vw.csets.push_back(ui::Configset(odv));
		return;
	}

	unordered_map<int, int> psId2Cset;
	pinsetsToViewConfigsets(psv, vw, psId2Cset);
	// ... and then "fix" the default set to use all Orderables, none may have been linked to default set
	vw.csets[0].orderables() = odv;

	int csetIdx = 0, prntId = 0;
	for ( db::Orderable &o : odv ) {
		// check if orderable has a pinset assigned; it may not when it's a new orderable for this datasheet AFTER assigning signals
		if ( o.pinset.id != 0 ) {
			assert(psId2Cset.find(o.pinset.id) != psId2Cset.end());
			csetIdx = psId2Cset[o.pinset.id];
			vw.csets[csetIdx].add(o);

			prntId = o.pinset.parentId;
			// this should actually be a while-loop, parent of parent etc until default set; unless it can only happen for default
			if ( prntId != 0 ) {
				csetIdx = psId2Cset[o.pinset.parentId];
				vw.csets[csetIdx].pinsetIdFor(o.pkg, o.pinset.parentId);
			}
		}
	}

	// create view objects in advance to reduce complexity in conversion code below
	int maxDsIdx = -1; // -1, not 0; otherwise no signalsets result in 1 PinView!!!
	for ( const db::Signalset &ss : ssv ) {
		maxDsIdx = max(maxDsIdx, ss.datasheetIdx);
	}
	for ( int i = 0; i <= maxDsIdx; i++ ) {
		vw.pinViews.push_back(vw.createNewPinView());
	}

	// TODO: is this correct? first looping pinsets, then orderables since they're needed for pins
	for ( const db::Pinset &ps : psv ) {
		csetIdx = psId2Cset[ps.id];

		for ( const pair<const Pin, db::Signalset> &pr : ps.signalsets ) {
			Pin p = pr.first;
			db::Signalset ss = pr.second;

			ui::PinView &pv = vw.pinViews[ss.datasheetIdx];
			pv.cviews[csetIdx].signalsetId = ss.id;
			pv.cviews[csetIdx].signals = ss.signals;
			for ( const db::Orderable &o : odv ) {
				if ( o.pinset.id == ps.id || o.pinset.parentId == ps.id ) {
					pv.pins[o.pkg] = p;
					break;
				}
			}
		}
	}
}

/* Essentially this function recreates all database objects and links from view objects.
 * It doesn't try to merge anything, but rather sets ids and re-creates what should be in the database.
 * Doing this is the best option since view changes are the purview of the ui and (logic) changes there
 * shouldn't result in modifications to this function.
 */
void convertAndSaveViewToDb(sqlite3 *db, ui::PinSetView &vw) {
	vector<db::Signalset> signalsets, parents;
	unordered_map<int, db::Pinset> pinsets;	    // key->object, no parents required to keep?
	unordered_map<string, int> odblPinsetLinks; // key->pinset id for linking!
	// save signalsets one config set at a time; parenting then by index
	// unordered_map<string, db::Orderable> odbls; // id->object
	int ssIdx = 0, csetIdx = 0;
	for ( ui::Configset &cs : vw.csets ) {
		ssIdx = 0;
		for ( const ui::PinView &pv : vw.pinViews ) {
			ui::PinView::ConfigView cv = pv.cviews[csetIdx];
			db::Signalset ss;
			ss.id = cv.signalsetId;
			ss.datasheetIdx = ssIdx;
			ss.signals = cv.signals;
			if ( !parents.empty() ) {
				db::Signalset &pt = parents[ssIdx];
				// reference parent's parent (furthest we can go) if parent is empty!
				ss.parentId = pt.signals.empty() ? pt.parentId : pt.id;
				// only save signalset if it's different from its parent
				// based on id, if zero this also works (parent is already saved, thus has a valid id)
				if ( !ss.signals.empty() ) {
					// db::saveOrUpdateSignalset(db, ss);
				} else {
					// to ensure that deeper parents do not use this set as parent!
					// BUT ... this will link to this signalset now while it shouldn't???
					// ss = pt;
				}
			}
			if ( ss.id != 0 || !ss.signals.empty() ) { // if it originally came from the DB or is not empty: save!
				db::saveOrUpdateSignalset(db, ss);
			}
			signalsets.push_back(ss); // always added to list for linking, even if same as parent
			ssIdx++;
		}

		// recreate ALL (incl. parent) pinsets from scratch, in case parents have changed! (i.e. configset changes)
		for ( db::Orderable &o : cs.orderables() ) {
			// also catches null(0)-id!
			int id = cs.pinsetIdFor(o.pkg);
			if ( pinsets.find(id) == pinsets.end() ) {
				db::Pinset ps;
				ps.id = id;

				if ( csetIdx > 0 ) {
					// with non-linear parents cannot assume previous set is parent!
					// search for first that contains the same orderable, will eventually end up in default
					bool foundParentConfig = false;
					for ( int pntIdx = csetIdx - 1; !foundParentConfig && pntIdx >= 0; pntIdx-- ) {
						if ( vw.csets[pntIdx].contains(o) ) {
							ps.parentId = vw.csets[pntIdx].pinsetIdFor(o.pkg);
							assert(pinsets.find(ps.parentId) != pinsets.end());
							foundParentConfig = true;
							break;
						}
					}
				}

				db::saveOrUpdatePinset(db, ps); // pinset is saved to ensure id is valid
				pinsets[ps.id] = ps;
				cs.pinsetIdFor(o.pkg, ps.id);
				odblPinsetLinks[o.name] = cs.pinsetIdFor(o.pkg);
			}
		}

		ssIdx = 0;
		for ( const ui::PinView &pv : vw.pinViews ) {
			// using fact that PinView is present even if no pins present and
			// for every config set the same amount of signalsets exist in-memory
			db::Signalset &ss = signalsets[ssIdx];
			if ( !ss.signals.empty() ) {
				for ( const pair<const Package, Pin> &pr : pv.pins ) {
					int psId = cs.pinsetIdFor(pr.first);
					assert(pinsets.find(psId) != pinsets.end());
					db::Pinset &ps = pinsets[psId];
					if ( !pr.second.empty() ) {
						ps.signalsets[pr.second] = ss;
						ps.pins++;
					}
					pinsets[psId] = ps; // TODO: REQUIRED???
				}
			}
			ssIdx++;
		}

		parents = signalsets;
		signalsets.clear();
		csetIdx++;
	}

	// these are saved only here to prevent an insert in each configset
	for ( const pair<const int, db::Pinset> &pr : pinsets ) {
		db::Pinset ps = pr.second;
		db::saveOrUpdatePinset(db, ps);
	}

	for ( const pair<const string, int> &pr : odblPinsetLinks ) {
		db::Orderable tmp;
		tmp.name = pr.first;
		tmp.pinset.id = pr.second;
		db::linkOrderableToItsPinset(db, tmp);
	}
}
