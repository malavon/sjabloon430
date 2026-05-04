#include <getopt.h>
#include <sysexits.h>

#include <fstream>
#include <iostream>
#include <unordered_map>

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

void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links);
void insertOrUpdatePackages(sqlite3 *db, ifstream &packages);

const string INSERT_DEVICE = "INSERT INTO device (datasheet_id,model,freq_max,storage_bytes,"
			     "ram_bytes,gpio_count,uart_count,usb_count,i2c_count,spi_count,"
			     "comp_count,timer_count,op_temp_min,op_temp_max,comment) ";

}}}

namespace dbf = sjabloon430::tools::db;
using namespace sjabloon430::tools::device;

int main(int argc, char **argv) // opties voor elke .txt file? misschien niet slecht?
{
	ifstream datasheets, families, links, packages;
	bool verbose = false;

	int opt;
	while ( (opt = getopt(argc, argv, "d:f:l:p:hv")) != -1 ) {
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
			case 'p':
				packages.open(optarg);
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
	if ( argc < optind ) {
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

	// read msp430-family.txt for devices (export van TI website! niet modificeren)
	// read packages.txt (extracted frod:m datasheets)
	// extend packages.txt? niet ieder DS heeft devices in header; meeste wel
	//  - mogelijk: proberen, indien 1 optie: OK, anders vragen?
	//  - of beter?: lijst van links, die resolutie zou 99% ok moeten zijn op dit moment
	//      - wiel niet opnieuw uitvinden, maar geen manuele verificatie op deze manier?
	// MAAR: zitten toch nog altijd met de matching van mcu & package
	// EN: niet elke match is op naam te doen!
	// OPLOSSING: derde txt file aangemaakt met device & datasheet
	if ( families.is_open() && links.is_open() ) {
		insertOrUpdateFamilies(sqlite, families, links);
	} else {
		cout << "No families & links read " << endl;
	}

	if ( packages.is_open() ) {
		insertOrUpdatePackages(sqlite, packages);
	} else {
		cout << "No packages read" << endl;
	}

	sqlite3_close(sqlite);
	return 0;
}

namespace sjabloon430 { namespace tools { namespace device {

string nextTSV(string &line, int &tab1, int &tab2) {
	int temp = tab1;
	tab2 = line.find('\t', tab1);
	tab1 = tab2 + 1;
	if ( tab2 >= 0 ) {
		return line.substr(temp, tab2 - temp);
	} else { // last column, no more tabs afterwards, tab2 == -1
		return line.substr(temp, line.length());
	}
}

void addNextString(string &query, const string value) {
	query.push_back('\'');
	query += value;
	query.push_back('\'');
	query.push_back(',');
}

// add multiple strings, all quoted and split on separator, hard-coded comma
// TI export doesn't have following whitespace, but if it is, TODO: trim in this function
void addStringsIn(string &query, string values) {
	int sep = values.find(',');
	// cout << sep << "NSERTING into " << values << endl;
	while ( sep > 0 ) {
		values.insert(sep + 1, "'");
		values.insert(sep, "'");
		sep = values.find(',', sep + 3);
		// cout << sep << "NSERTING into " << values << endl;
	}

	query.push_back('\'');
	query.append(values);
	query.push_back('\'');
}

void addNextInteger(string &query, string value) {
	// no quotes, numbers are simply inserted (even though they are floating-point)
	query.append(value.empty() ? "0" : value);
	query.push_back(',');
}

void addGroupFeatures(sqlite3 *db, vector<string> &features, const string &part, const string &text, const string &group,
		      const string &param1 = "", const string &param2 = "", const string &param3 = "") {
	if ( text.empty() || group.empty() ) {
		return;
	}
	static const string INSERT_QUERY = "INSERT INTO device_feature (device_id,feature_id,param1,param2,param3,comment) "
					   "VALUES ( (SELECT id FROM device WHERE model = ";

	// comma-separated values ... select using IN-statement
	string select = "SELECT id "
			"FROM feature "
			"WHERE family_group = '"
		      + group + "' AND family_text IN (";
	addStringsIn(select, text);
	select += ");";

	sqlite3_stmt *stmt;
	if ( sqlite3_prepare_v2(db, select.c_str(), -1, &stmt, NULL) != SQLITE_OK ) {
		cout << "SQLite3 error " << sqlite3_errmsg(db) << endl;
		return;
	}

	while ( sqlite3_step(stmt) == SQLITE_ROW ) {
		// BAD IDEA, but even in a C++ wrapper for SQLite this is done the same way
		// this won't work for anything that isn't 8-byte characters (e.g. unicode)
		// but it's fine for this use since *I* control the input anyway
		string featureId(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));

		string insert = INSERT_QUERY;
		addNextString(insert, part);
		insert[insert.length() - 1] = ')'; // finish sub-query
		insert += ',';			   // add comma afterwards
		addNextString(insert, featureId);
		addNextString(insert, param1.empty() ? "NULL" : param1);
		addNextString(insert, param2.empty() ? "NULL" : param2);
		addNextString(insert, param3.empty() ? "NULL" : param3);
		addNextString(insert, "AUTOMATIC_RESOLUTION");
		insert[insert.length() - 1] = ')';
		features.push_back(insert);
	}
}

// TODO: actually only inserts right now :)
void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links) {
	string line;
	// read links in map first

	unordered_map<string, string> datasheets;
	while ( getline(links, line) ) {
		// expected <device>\t<datasheet>
		// e.g. MSP430FR2533	SLAS942
		unsigned int tab = line.find('\t');
		datasheets[line.substr(0, tab)] = line.substr(tab + 1);
		// cout << "datasheet '" << line.substr(tab+1) << "' for device '" << line.substr(0, tab) << "'" << endl;
	}

	int tab1, tab2; // not unsigned, string::find() returns -1 :)
	string value, part, adc;
	// insert queries to be executed later because foreign key is not yet satisfied
	vector<string> featureLinks;
	// no, this isn't efficient, but it's fine for this program
	string query;
	// first line contains header, but no datasheet will be found anyway
	while ( getline(families, line) ) {
		featureLinks.clear();
		tab1 = 0;

		query = INSERT_DEVICE;
		query.append(" VALUES ( ");

		// Datasheet link & Part
		part = nextTSV(line, tab1, tab2);
		// TODO: if NULL, should fail? (database will error anyway)
		addNextString(query, datasheets[part]);
		addNextString(query, part);

		// Frequency (MHz)
		addNextInteger(query, nextTSV(line, tab1, tab2));
		// value memory (kByte)
		// TODO: replace 0.13 with 0.125 ...
		value = nextTSV(line, tab1, tab2);
		value += "*1024";
		addNextInteger(query, value);
		// RAM (kByte)
		value = nextTSV(line, tab1, tab2);
		if ( value == "0.13" ) {
			addNextInteger(query, "0.125*1024");
		} else {
			value += "*1024";
			addNextInteger(query, value);
		}
		// ADC type
		adc = nextTSV(line, tab1, tab2);
		// Number of ADC channels (these are external channels only)
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, featureLinks, part, adc, "ADC", value);

		// Number of GPIOs
		addNextInteger(query, nextTSV(line, tab1, tab2));

		// UART
		addNextInteger(query, nextTSV(line, tab1, tab2));

		// USB
		value = nextTSV(line, tab1, tab2);
		if ( value == "Yes" ) {
			addNextInteger(query, "1");
		} else {
			addNextInteger(query, "0");
		}

		// Number of I2Cs
		addNextInteger(query, nextTSV(line, tab1, tab2));
		// SPI
		addNextInteger(query, nextTSV(line, tab1, tab2));
		// Number of comparator channels
		addNextInteger(query, nextTSV(line, tab1, tab2));
		// Timers - 16-bit
		addNextInteger(query, nextTSV(line, tab1, tab2));

		// Bootloader (BSL)
		// TODO: features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, featureLinks, part, value, "BSL");

		// Special I/O
		// TODO: features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(db, featureLinks, part, value, "Special I/O");

		// Operating temperature range (°C)
		// "(-)n(n) to mm(m)"
		value = nextTSV(line, tab1, tab2);
		tab2 = value.find(" to ");
		addNextInteger(query, value.substr(0, tab2));
		addNextInteger(query, value.substr(tab2 + 4, value.length() - tab2 - 4));

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
		addGroupFeatures(db, featureLinks, part, value, "Features");

		// Comment
		addNextString(query, "TI EXPORT");
		query[query.length() - 1] = ')';

		// insert or update in device table
		if ( sqlite3_exec(db, query.c_str(), NULL, NULL, NULL) == SQLITE_OK ) {
			cout << "SUCCESS " << query << endl;
			for ( string &q : featureLinks ) {
				if ( sqlite3_exec(db, q.c_str(), NULL, NULL, NULL) != SQLITE_OK ) {
					cout << " FAILED ";
				} else {
					cout << "SUCCESS ";
				}
				cout << q << endl;
			}
		} else {
			cout << " FAILED " << query << endl;
		}
	}
}

// find devices for datasheet, match on models lexicologically
// very naive way, matching with one letter less each time
// use the best (top) match only
// if SQLite3 has a function I can use for this, I didn't find it
// custom function would have worked too, but not necessary in this case
string findBestDeviceMatch(sqlite3 *db, const string &orderable, const string &datasheet) {
	string select = "SELECT id, model, ";
	// packages sometimes requires a few characters only to match, don't skimp
	for ( int i = orderable.length(); i > 2; i-- ) {
		const string substr = orderable.substr(0, i);
		const string idx(to_string(i));
		select += to_string(i) + " * instr ( model, '";
		select += substr;
		select += "' ) + ";
	}

	select += "0 as matching FROM device WHERE datasheet_id ='" + datasheet + "' order by matching desc limit 1;";
	// cout << select << endl;
	sqlite3_stmt *stmt;
	if ( sqlite3_prepare_v2(db, select.c_str(), -1, &stmt, NULL) != SQLITE_OK || sqlite3_step(stmt) != SQLITE_ROW ) {
		cout << "SQLite3 error in device match " << sqlite3_errmsg(db) << endl;
		return "-1";
	}

	// TODO: match strength would be useful to add in comment?
	string id(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
	return id;
}

void insertOrUpdatePackages(sqlite3 *db, ifstream &packages) {
	static const string INSERT_PACKAGE = "INSERT INTO package (drawing,pins,type,comment) VALUES (";
	static const string INSERT_ORDERABLE =
	    "INSERT INTO orderable "
	    "(name,device_id,drawing,pins,status,msl_level,op_temp_min,op_temp_max,comment) VALUES (";

	int tab1, tab2;
	string line;
	string orderable, deviceId, datasheet, status, type, drawing, pins, msl, temp, tempMin, tempMax;
	// no, this isn't efficient, but it's fine for this program
	string insPackage, insOrderable;
	while ( getline(packages, line) ) {
		tab1 = 0;

		insPackage = INSERT_PACKAGE;
		insOrderable = INSERT_ORDERABLE;

		// defer query building until later, modifications may occur
		orderable = nextTSV(line, tab1, tab2);
		datasheet = nextTSV(line, tab1, tab2);

		deviceId = findBestDeviceMatch(db, orderable, datasheet);
		status = nextTSV(line, tab1, tab2);
		type = nextTSV(line, tab1, tab2);
		drawing = nextTSV(line, tab1, tab2);
		pins = nextTSV(line, tab1, tab2);
		msl = nextTSV(line, tab1, tab2);
		temp = nextTSV(line, tab1, tab2);

		// parse -40_to_85 (IF CORRECT)
		int pos;
		if ( (pos = temp.find('_')) > 0 ) {
			tempMin = temp.substr(0, pos);
			if ( (pos = temp.find('_', pos + 1)) > 0 ) {
				tempMax = temp.substr(pos + 1, 3);
			}
		}
		// transform MSL into simple integer level, default to 3
		// Level-3-260C-168_HR
		// Level-2-260C-1_YEAR
		// Level-1-260C-UNLIM
		if ( msl.length() > 7 ) {
			msl = msl.at(6);
		}
		if ( msl != "3" && msl != "2" && msl != "1" ) {
			msl = "3";
		}

		// package insert
		addNextString(insPackage, drawing);
		addNextInteger(insPackage, pins);
		addNextString(insPackage, type);
		// Comment
		addNextString(insPackage, "AUTOMATIC INSERTION");
		insPackage[insPackage.length() - 1] = ')';

		if ( sqlite3_exec(db, insPackage.c_str(), NULL, NULL, NULL) == SQLITE_OK ) {
			cout << "SUCCESS " << insPackage << endl;
		} else {
			cout << " FAILED " << insPackage << endl;
		}

		// insert orderable, even if package has failed (might be duplicate)
		addNextString(insOrderable, orderable);
		addNextInteger(insOrderable, deviceId);
		addNextString(insOrderable, drawing); // FK to package
		addNextInteger(insOrderable, pins);   // FK to package
		addNextString(insOrderable, status);
		addNextInteger(insOrderable, msl);
		addNextInteger(insOrderable, tempMin);
		addNextInteger(insOrderable, tempMax);
		addNextString(insOrderable, "AUTOMATIC RESOLUTION");
		insOrderable[insOrderable.length() - 1] = ')';

		if ( sqlite3_exec(db, insOrderable.c_str(), NULL, NULL, NULL) == SQLITE_OK ) {
			cout << "SUCCESS " << insOrderable << endl;
		} else {
			cout << " FAILED " << insOrderable << endl;
		}
	}

	// some manual corrections?
	// MSP4301103IPWR -> MSP430AFE253
	// SN0806723IPNR -> MSP430F6723
	// MSP430G2113IN20 -> removed from datasheets, orderable still present
	// MSP430G2453IPW0RQ1 -> 2453 Q1 not in family (LIFEBUY in 2014 ...)
	// MSP430G2453IPW8RQ1 -> 2453 Q1 not in family (LIFEBUY in 2014 ...)
}

}}} // namespace sjabloon430::tools::device
