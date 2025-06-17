#include <getopt.h>
#include <sysexits.h>

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "database-files.hpp"
#include "database.hpp"

using namespace std;

namespace sjabloon430 { namespace tools { namespace device {

void printUsage() {
	cout << "Usage: devices [-hv] "
	     << "[-d <datasheets-file>] "
	     << "[-f <families-file>] "
	     << "[-l <links-file>] "
	     << "[-o <orderables-file>] <sqlite3db>" << endl;

	cout << "<datasheets-file> is a tab-separated file containing records of:\n"
	     << "\tSheet\tRev.\tIssued Month\tIssued Year\tRevised Month\tRevised Year\n"
	     << "e.g.\tSLAS380\tF\t4\t2004\t3\t2022\n\n";

	cout << "<families-file> is a tab-separated file exported from the TI website "
		"and converted to tsv containing records of:\n"
	     << "\tPart\tFrequency\tNonvolatile Memory\tRAM\tADC Type etc\n\n";

	cout << "<links-file> is a tab-separated file containing records of:\n"
	     << "\tPart Number\tSheet\n"
	     << "e.g.\tMSP430FR2533\tSLAS942\n\n";

	cout << "<orderables-file> is a tab-separated file containing records of:\n"
	     << "\tOrderable\t\tSheet\tStatus\tPackage\tDrawing\t# Pins\tMSL\n"
	     << "e.g.\tMSP430FR2533IRHBT\tslas942\tACTIVE\tVQFN\tRHB\t32\tLevel-2-260C-1_YEAR\n";
}

template<class T>
T nextTSV(const string &line, int &tab1, int &tab2);

void insertOrUpdateDatasheets(sqlite3 *db, ifstream &datasheets);
void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links);
void insertOrUpdateOrderables(sqlite3 *db, ifstream &);

}}}

namespace dbf = sjabloon430::tools::db;
using namespace sjabloon430::tools::device;

int main(int argc, char **argv) // opties voor elke .txt file? misschien niet slecht?
{
	ifstream datasheets, families, links, orderables;
	bool verbose = false;

	int opt;
	while ( (opt = getopt(argc, argv, "d:f:l:o:hv")) != -1 ) {
		switch ( opt ) {
			case 'd':
				datasheets.open(optarg);
				break;
			case 'f':
				families.open(optarg);
				break;
			case 'l':
				links.open(optarg);
				break;
			case 'o':
				orderables.open(optarg);
				break;
			case 'v':
				verbose = true;
				break;
			case 'h':
			default:
				printUsage();
				return EX_USAGE;
		}
	}
	if ( argc <= 1 || (argc == 2 && verbose) || argc < optind ) {
		printUsage();
		return EX_USAGE;
	}

	sqlite3 *sqlite = db::createDatabase();
	if ( sqlite == nullptr ) {
		exit(-1);
	}

	dbf::importDatabase(sqlite, [&](const string &filename, const int lineNr, const char *error) {
		if ( error != nullptr ) {
			std::cerr << "Error: could not import SQL from " << filename << " (line " << lineNr << ") with error "
				  << error << std::endl;
		} else if ( verbose ) {
			std::cout << filename << '\t';
		}
	});

	if ( datasheets.is_open() ) {
		insertOrUpdateDatasheets(sqlite, datasheets);
	} else {
		cout << "No datasheets read " << endl;
	}
	if ( families.is_open() && links.is_open() ) {
		insertOrUpdateFamilies(sqlite, families, links);
	} else {
		cout << "No families & links read " << endl;
	}

	if ( orderables.is_open() ) {
		insertOrUpdateOrderables(sqlite, orderables);
	} else {
		cout << "No packages read" << endl;
	}

	// do all exports each time, if something changed that wasn't expected to be changed the user should notice this
	dbf::exportDatasheets(sqlite);
	dbf::exportPackages(sqlite);
	// getting all data instead of ids isn't necessary, but it doesn't hurt that much
	for ( const db::Datasheet &ds : db::findAll<db::Datasheet>(sqlite) ) {
		dbf::exportDataForDatasheet(sqlite, ds.id);
	}

	sqlite3_close(sqlite);
	return 0;
}

namespace sjabloon430 { namespace tools { namespace device {

string nextTSV(const string &line, int &tab1, int &tab2) {
	int temp = tab1;
	tab2 = line.find('\t', tab1);
	tab1 = tab2 + 1;
	if ( tab2 >= 0 ) {
		return line.substr(temp, tab2 - temp);
	} else { // last column, no more tabs afterwards, tab2 == -1
		return line.substr(temp, line.length());
	}
}

template<>
int nextTSV<int>(const string &line, int &tab1, int &tab2) {
	string token = nextTSV(line, tab1, tab2);
	return token.empty() ? 0 : stoi(token);
}

// text can be comma-separated text!
void addGroupFeatures(sqlite3 *db, db::Device &dv, const string &text, const string &group, const string &p1 = "",
		      const string &p2 = "", const string &p3 = "") {
	if ( text.empty() ) {
		return; // easy way out
	}

	static const char COMMA(',');
	vector<string> tokens; // is there a C++ function to do this for me???
	size_t end = text.find(COMMA), start = 0;
	do {
		tokens.push_back(end == string::npos ? text.substr(start) : text.substr(start, end - start));
		start = end + 1;
		end = text.find(start, COMMA);
	} while ( start != string::npos + 1 );

	vector<string> fts = db::findDeviceFeatureIds(db, group, tokens);
	for ( const string &id : fts ) {
		if ( id.find("IGNORE_") == string::npos ) {
			dv.features.push_back(db::Device::Feature{
				id, {p1, p2, p3}
				});
		}
	}
}

void insertOrUpdateDatasheets(sqlite3 *db, ifstream &datasheets) {
	string line;
	int tab1, tab2;
	while ( getline(datasheets, line) ) {
		tab1 = 0;
		// expected <datasheet>\t<rev>\issuedtmonth\tissuedyear\trevmonth\trevyear; all FILLED!
		// e.g. SLAS942	E	11	2015	12	2019
		db::Datasheet ds;
		ds.id = nextTSV(line, tab1, tab2);
		ds.rev = nextTSV(line, tab1, tab2);
		ds.issued.month = nextTSV<int>(line, tab1, tab2);
		ds.issued.year = nextTSV<int>(line, tab1, tab2);
		ds.revised.month = nextTSV<int>(line, tab1, tab2);
		ds.revised.year = nextTSV<int>(line, tab1, tab2);

		db::saveOrUpdate(db, ds);
	}
}

void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links) {
	string line;

	// read links in map first
	unordered_map<string, string> datasheets;
	while ( getline(links, line) ) {
		// expected <device>\t<datasheet>
		// e.g. MSP430FR2533	SLAS942
		unsigned int tab = line.find('\t');
		datasheets[line.substr(0, tab)] = line.substr(tab + 1);
	}

	int tab1, tab2; // not unsigned, string::find() returns -1 :)
	string value, adc;
	// first line contains header, discard it
	getline(families, line);
	while ( getline(families, line) ) {
		tab1 = 0;
		db::Device dv;

		dv.model = nextTSV(line, tab1, tab2);
		// TODO: if NULL, should fail? (database will error anyway)
		dv.datasheetId = datasheets[dv.model];

		dv.maxFreq = nextTSV<int>(line, tab1, tab2);
		dv.storage = 1024 * nextTSV<int>(line, tab1, tab2);

		// RAM (kByte)
		value = nextTSV(line, tab1, tab2);
		dv.ram = (value == "0.13") ? 0.125 * 1024 : stod(value) * 1024;
		// ADC type
		adc = nextTSV(line, tab1, tab2);
		// Number of ADC channels (these are external channels only)
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, dv, adc, "ADC", value);

		dv.ngpio = nextTSV<int>(line, tab1, tab2);
		dv.nuart = nextTSV<int>(line, tab1, tab2);
		dv.nusb = nextTSV(line, tab1, tab2) == "Yes" ? 1 : 0;
		dv.ni2c = nextTSV<int>(line, tab1, tab2);
		dv.nspi = nextTSV<int>(line, tab1, tab2);
		dv.ncomp = nextTSV<int>(line, tab1, tab2);
		dv.ntimer = nextTSV<int>(line, tab1, tab2);

		// Bootloader (BSL)
		// TODO: features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, dv, value, "BSL");

		// Special I/O
		// TODO: features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, dv, value, "Special I/O");

		// Operating temperature range (°C)
		// "(-)n(n) to mm(m)"
		value = nextTSV(line, tab1, tab2);
		tab2 = value.find(" to ");
		dv.opTempMin = stoi(value.substr(0, tab2));
		dv.opTempMax = stoi(value.substr(tab2 + 4, value.length() - tab2 - 4));

		// not saved (or not in device table)
		// Price|Quantity (USD)
		nextTSV(line, tab1, tab2);
		// Package type
		nextTSV(line, tab1, tab2);
		// Pin count
		nextTSV(line, tab1, tab2);
		// Package area (mm^2)
		nextTSV(line, tab1, tab2);
		// Package size (L x W) (mm)
		nextTSV(line, tab1, tab2);

		// Features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, dv, value, "Features");

		db::saveOrUpdate(db, dv);
	}
}

void insertOrUpdateOrderables(sqlite3 *db, ifstream &input) {
	int tab1, tab2;
	string line, temp;
	unordered_set<db::Package> pkgs; // cache saved packages, no need to re-save if already in DB
	while ( getline(input, line) ) {
		tab1 = 0;

		db::Orderable o;

		// defer query building until later, modifications may occur
		o.name = nextTSV(line, tab1, tab2);
		temp = nextTSV(line, tab1, tab2); // datasheet, used only to find best device match
		o.model = db::findDeviceMatchFor(db, temp, o.name);
		o.status = nextTSV(line, tab1, tab2);
		o.pkg.type = nextTSV(line, tab1, tab2);
		o.pkg.drawing = nextTSV(line, tab1, tab2);
		o.pkg.pins = nextTSV<int>(line, tab1, tab2);

		temp = nextTSV(line, tab1, tab2); // MSL

		// transform MSL into simple integer level, default to 5
		// Level-4-260C-72 HR
		// Level-3-260C-168_HR
		// Level-2-260C-1_YEAR
		// Level-1-260C-UNLIM
		if ( temp.length() > 7 ) {
			temp = temp.at(6);
			o.msl = temp[0] < '1' || temp[0] > '4' ? 5 : stoi(temp);
			temp = nextTSV(line, tab1, tab2); // temperature
		} else {
			// MSL isn't MSL; do not get next token but reuse this one
			o.msl = 5;
		}

		// parse -40_to_85 (IF CORRECT)
		int pos;
		if ( (pos = temp.find('_')) > 0 ) {
			o.opTempMin = stoi(temp.substr(0, pos));
			if ( (pos = temp.find('_', pos + 1)) > 0 ) {
				o.opTempMax = stoi(temp.substr(pos + 1, 3));
			}
		}

		if ( pkgs.find(o.pkg) == pkgs.end() ) {
			db::saveOrUpdate(db, o.pkg);
			pkgs.insert(o.pkg);
		}
		db::saveOrUpdate(db, o);
	}

	// some manual corrections?
	// MSP4301103IPWR -> MSP430AFE253
	// SN0806723IPNR -> MSP430F6723
	// MSP430G2113IN20 -> removed from datasheets, orderable still present
	// MSP430G2453IPW0RQ1 -> 2453 Q1 not in family (LIFEBUY in 2014 ...)
	// MSP430G2453IPW8RQ1 -> 2453 Q1 not in family (LIFEBUY in 2014 ...)
}

}}} // namespace sjabloon430::tools::device
