
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

void convertDbToView(const vector<db::Signalset> &, vector<db::Orderable> &, ui::PinSetView &);
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
		convertDbToView(signalsets, ordbls, vw);

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

void convertDbToView(const vector<db::Signalset> &ssv, vector<db::Orderable> &odv, ui::PinSetView &vw) {
	// logic: * all pinsets without parents are part of the default config set
	//	  * all pinsets that have default pinsets as parent, are the second config set
	//	  * all pinsets that have second ... etc
	set<int> pids = {0};
	while ( !pids.empty() ) {
		set<int> nextPids;
		ui::Configset cs;

		for ( db::Orderable &o : odv ) {
			// also catches non-existent pinsets!
			if ( pids.find(o.pinset.parentId) != pids.end() ) {
				if ( o.pinset.id != 0 ) {
					// id can be 0 WHEN orderable has NO pinset linked yet; 0 signifies NULL
					nextPids.insert(o.pinset.id);
				}
				cs.add(o);
				cs.pinsetIdFor(o.pkg, o.pinset.id);
			}
		}
		// if this assert hits, there are 2 configsets with the same parent ... which is not supported
		// either the user has made a big error, or there are datasheets in which this is really, really
		// required (in which case my message to the reader is: sorry ... <hihi>)
		assert(nextPids.size() <= vw.pkgs.size());
		vw.addIfNotEmpty(cs);

		pids = nextPids;
	}

	// create view objects in advance to reduce complexity in conversion code below
	int maxDsIdx = -1; // -1, not 0; otherwise no signalsets result in 1 PinView!!!
	for ( const db::Signalset &ss : ssv ) {
		maxDsIdx = max(maxDsIdx, ss.datasheetIdx);
	}
	for ( int i = 0; i <= maxDsIdx; i++ ) {
		vw.pinViews.push_back(vw.createNewPinView());
	}

	int csetIdx = 0;
	for ( const ui::Configset &cs : vw.csets ) {
		for ( const db::Orderable &o : cs.orderablesView() ) {
			for ( const pair<Pin, db::Signalset> &pr : o.pinset.signalsets ) {
				Pin p = pr.first;
				db::Signalset ss = pr.second;

				ui::PinView &pv = vw.pinViews[ss.datasheetIdx];
				// only set signals if id not same as parent (OK because it's coming straight from DB)
				if ( csetIdx == 0 || ss.id != pv.cviews[csetIdx - 1].signalsetId ) {
					pv.cviews[csetIdx].signalsetId = ss.id;
					pv.cviews[csetIdx].signals = ss.signals;
				}
				pv.pins[o.pkg] = p;
			}
		}
		csetIdx++;
	}

	// ... and then "fix" the default set to use all Orderables
	vw.csets[0].orderables() = odv;
}

/* Essentially this function recreates all database objects and links from view objects.
 * It doesn't try to merge anything, but rather sets ids and re-creates what should be in the database.
 * Doing this is the best option since view changes are the purview of the ui and (logic) changes there
 * shouldn't result in modifications to this function.
 */
void convertAndSaveViewToDb(sqlite3 *db, ui::PinSetView &vw) {
	vector<db::Signalset> signalsets, parents; // kept locally only?
	// save signalsets one config set at a time; parenting then by index
	// unordered_map<string, db::Orderable> odbls; // id->object
	int ssIdx = 0, cIdx = 0;
	for ( ui::Configset &cs : vw.csets ) {
		ssIdx = 0;
		for ( const ui::PinView &pv : vw.pinViews ) {
			ui::PinView::ConfigView cv = pv.cviews[cIdx];
			db::Signalset ss;
			ss.id = cv.signalsetId;
			ss.datasheetIdx = ssIdx;
			ss.signals = cv.signals;
			if ( parents.empty() ) {
				db::saveOrUpdateSignalset(db, ss);
			} else {
				db::Signalset &pt = parents[ssIdx];
				ss.parentId = pt.id;
				// only save signalset if it's different from its parent
				// based on id, if zero this also works (parent is already saved, thus has a valid id)
				if ( pt.id != ss.id && !ss.signals.empty() ) { // signals can contain all empty strings ...
					db::saveOrUpdateSignalset(db, ss);
				} else {
					ss = pt;
				}
			}
			signalsets.push_back(ss); // always added to list for linking, even if same as parent
			ssIdx++;
		}

		// recreate all pinsets from view objects
		for ( db::Orderable &o : cs.orderables() ) {
			o.pinset.pins = 0;		     // will be calculated
			o.pinset.id = cs.pinsetIdFor(o.pkg); // can be zero if new
			if ( cIdx > 0 ) {
				o.pinset.parentId = vw.csets[cIdx - 1].pinsetIdFor(o.pkg);
			}

			db::saveOrUpdatePinset(db, o.pinset); // pinset is saved to ensure id is valid
			cs.pinsetIdFor(o.pkg, o.pinset.id);   // and then id is updated in view
		}

		ssIdx = 0;
		for ( const ui::PinView &pv : vw.pinViews ) {
			// using fact that PinView is present even if no pins present and
			// for every config set the same amount of signalsets exist in-memory
			db::Signalset &ss = signalsets[ssIdx];
			if ( ss.signals.empty() && !parents.empty() ) {
				ss = parents[ssIdx];
			}
			for ( const pair<Package, Pin> &pr : pv.pins ) {
				for ( db::Orderable &o : cs.orderables() ) {
					if ( o.pkg == pr.first && !pr.second.empty() ) {
						o.pinset.signalsets[pr.second] = ss;
						o.pinset.pins++;
					}
				}
			}
			ssIdx++;
		}

		// since each set is superset of the next and subset of the previous, orderables & pinsets will be
		// updated and linked first in default set, then maybe again in next set and maybe again later
		// it's not perfect, but it is required to save orderables/pinsets that are ONLY part of the current set
		// so that the database ids are valid for parenting later!
		for ( db::Orderable &o : cs.orderables() ) {
			db::saveOrUpdatePinset(db, o.pinset); // pinset is saved AGAIN for pin count
			db::linkOrderableToItsPinset(db, o);
		}

		parents = signalsets;
		signalsets.clear();
		cIdx++;
	}
}
