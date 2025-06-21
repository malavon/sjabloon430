
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
		Window pins(LINES - 6, COLS - WIN_CONFIGSET_WIDTH, 6, 0);
		pins.optionScrollable(Toggle::ON);
		BorderedWindow configs(LINES, WIN_CONFIGSET_WIDTH, 0, COLS - WIN_CONFIGSET_WIDTH);
		configs.setTitle("Configsets");

		Window &statusWin = pins;
		statusWin.add(0, 0, "Importing SQLite DB:");
		int files = 0, errors = 0;
		dbf::importDatabase(db, [&](const string &filename, const char *error) {
			files++;
			if ( error != nullptr ) {
				errors++;
				if ( errors < statusWin.maxRows() - WIN_TOP_HEIGHT - 2 /**/ ) {
					statusWin.print("\n  \"%s\" ERR: %s", filename.c_str(), error);
				} else if ( errors < statusWin.maxRows() - WIN_TOP_HEIGHT - 1 ) {
					statusWin.add("\n  ... more errors ...");
				}
			}
		});
		statusWin.print("\n %d files imported ", files);
		statusWin.print(errors == 0 ? "without errors\n" : "with %d errors\n", errors);
		statusWin.paint();

		// initial state: open search window
		string selectedId = ui::searchDatasheet(db::listAllModelsAndDatasheets(db), WIDEST_MODEL_LENGTH);
		db::Datasheet selectedDS = db::findDatasheet(db, selectedId);

		db::DatabaseTotals totals = db::countTotals(db);
		db::DatabaseTotals supported = db::countSupported(db);

		ui::drawTopWindow(top, selectedDS, totals, supported);

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

		db::removeGapsInSignalsetIds(db);

		dbf::exportDataForDatasheet(db, selectedId);

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
					ui::Configset cs;
					vw.add(cs);
					pinsetsToViewConfigsets(psv, vw, id2cs, nextPids);
					nextPids.clear();
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
 */
void convertDbToView(const vector<db::Signalset> &ssv, vector<db::Pinset> &psv, vector<db::Orderable> &odv,
		     ui::PinSetView &vw) {
	// quick return in case there are no pinsets, it's the same result but much less work
	if ( psv.size() == 0 ) {
		vw.csets.push_back(ui::Configset(odv));
		return;
	}

	unordered_map<int, int> psId2Cset;
	pinsetsToViewConfigsets(psv, vw, psId2Cset);

	unordered_map<int, db::Pinset> id2Ps;
	for ( const db::Pinset &ps : psv ) {
		id2Ps[ps.id] = ps;
	}

	int csetIdx = 0, prntId = 0;
	for ( db::Orderable &o : odv ) {
		// check if orderable has a pinset assigned; it may not when it's a new orderable for this datasheet AFTER assigning signals
		if ( o.pinset.id == 0 ) {
			vw.csets[0].add(o);
		} else {
			assert(psId2Cset.find(o.pinset.id) != psId2Cset.end());
			csetIdx = psId2Cset[o.pinset.id];
			vw.csets[csetIdx].add(o);

			prntId = o.pinset.parentId;
			// keep adding to parent sets until no more parent; required for always-correct parent reconstruction
			while ( prntId != 0 ) {
				csetIdx = psId2Cset[prntId];
				vw.csets[csetIdx].add(o, prntId);
				prntId = id2Ps[prntId].parentId;
			}
		}
	}
	assert(vw.csets[0].orderablesView().size() == odv.size()); // DB consistency

	// create view objects in advance to reduce complexity in conversion code below
	int maxDsIdx = -1; // -1, not 0; otherwise no signalsets result in 1 PinView!!!
	for ( const db::Signalset &ss : ssv ) {
		maxDsIdx = max(maxDsIdx, ss.datasheetIdx);
	}
	for ( int i = 0; i <= maxDsIdx; i++ ) {
		vw.emplace();
	}

	// TODO: is this correct? first looping pinsets, then orderables since they're needed for pins
	for ( const db::Pinset &ps : psv ) {
		csetIdx = psId2Cset[ps.id];

		for ( const pair<Pin, db::Signalset> &pr : ps.signalsets ) {
			Pin p = pr.first;
			db::Signalset ss = pr.second;

			ui::PinView &pv = vw[ss.datasheetIdx];
			pv.cviews[csetIdx].signalsetId = ss.id;
			pv.cviews[csetIdx].signals = ss.signals;
			for ( const db::Orderable &o : odv ) {
				if ( o.pinset.id == ps.id || o.pinset.parentId == ps.id ) {
					pv.pins[o.pkg] = p;
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
	int ssIdx = 0, csetIdx = 0;
	for ( ui::Configset &cs : vw.csets ) {
		ssIdx = 0;
		for ( const ui::PinView &pv : vw ) {
			ui::PinView::ConfigView cv = pv.cviews[csetIdx];
			db::Signalset ss;
			ss.id = cv.signalsetId;
			ss.datasheetIdx = ssIdx;
			ss.signals = cv.signals;
			if ( !parents.empty() ) {
				db::Signalset &pt = parents[ssIdx];
				// reference parent's parent (furthest we can go) if parent is empty!
				ss.parentId = pt.signals.empty() ? pt.parentId : pt.id;
			}
			if ( ss.id != 0 || !ss.signals.empty() ) { // if it originally came from the DB or is not empty: save!
				db::saveOrUpdateSignalset(db, ss);
			}
			signalsets.push_back(ss); // always added to list for linking, even if same as parent
			ssIdx++;
		}

		// recreate ALL pinsets from scratch to ensure valid ids, parents are assigned as well!
		for ( db::Orderable &o : cs.orderables() ) {
			o.pinset.id = cs.pinsetIdFor(o.pkg);
			// also catches null(0)-id!
			if ( pinsets.find(o.pinset.id) == pinsets.end() ) {
				db::Pinset ps;
				ps.id = o.pinset.id;

				if ( csetIdx > 0 ) {
					// with non-linear parents cannot assume previous set is parent!
					// search for first that contains ALL orderables, will eventually end up in default
					for ( int pntIdx = csetIdx - 1; ps.parentId == 0 && pntIdx >= 0; pntIdx-- ) {
						if ( vw.csets[pntIdx].contains(cs.orderables()) ) {
							ps.parentId = vw.csets[pntIdx].pinsetIdFor(o.pkg);
							assert(pinsets.find(ps.parentId) != pinsets.end());
							break;
						}
					}
				}

				db::saveOrUpdatePinset(db, ps); // pinset is saved to ensure id is valid
				pinsets[ps.id] = ps;
				o.pinset = ps;
				cs.update(o); // also sets pinsetIdFor!
			}
			odblPinsetLinks[o.name] = o.pinset.id;
		}

		ssIdx = 0;
		for ( const ui::PinView &pv : vw ) {
			// using fact that PinView is present even if no pins present and
			// for every config set the same amount of signalsets exist in-memory
			db::Signalset &ss = signalsets[ssIdx];
			if ( !ss.signals.empty() ) {
				for ( const pair<Package, Pin> &pr : pv.pins ) {
					int psId = cs.pinsetIdFor(pr.first);
					// can be 0 when _this_ configset has less packages than view (i.e. other configsets)
					if ( psId != 0 ) {
						assert(pinsets.find(psId) != pinsets.end());
						db::Pinset &ps = pinsets[psId];
						if ( !pr.second.empty() ) {
							ps.signalsets[pr.second] = ss;
						}
					}
				}
			}
			ssIdx++;
		}

		assert(pinsets.find(0) == pinsets.end()); // safety check; algorithm depends on this heavily!
		parents = signalsets;
		signalsets.clear();
		csetIdx++;
	}

	for ( const pair<int, db::Pinset> &pr : pinsets ) {
		db::Pinset ps = pr.second;
		db::saveOrUpdatePinset(db, ps);
	}

	for ( const pair<string, int> &pr : odblPinsetLinks ) {
		db::Orderable tmp = {pr.first};
		tmp.pinset.id = pr.second;
		db::linkOrderableToItsPinset(db, tmp);
	}
}
