#include <getopt.h>
#include <sysexits.h>

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "sqlite3.h"

using namespace std;

void printUsage() {
	cout << "Usage: devices [-h] "
		 // << "[-d <datasheets-file>] "
		 << "[-f <families-file>] "
		 << "[-l <links-file>] "
		 << "[-p <packages-file>] <sqlite3db>\n\n";

	cout << "<families-file> is a SORTED tab-separated file exported from the TI website "
			"and converted to tsv containing records of:\n"
		 << "\tPart\tFrequency\tvalue Memory\tRAM\tADC Type etc\n\n";

	// cout << "<datasheets-file> is a tab-separated file containing records of:\n"
	// 	 << "\tSheet\tRev.\tIssued\tRevised\n"
	// 	 << "e.g.\tSLAS380\tF\t04/2004\t03/2022\n\n";

	cout << "<links-file> is a SORTED tab-separated file containing records of:\n"
		 << "\tPart Number\tSheet\n"
		 << "e.g.\tMSP430FR2533\tSLAS942\n\n";

	cout << "<packages-file> is a SORTED tab-separated file containing records of:\n"
		 << "\tOrderable\t\tSheet\tStatus\tPackage\tDrawing\t# Pins\tMSP\n"
		 << "e.g.\tMSP430FR2533IRHBT\tslas942\tACTIVE\tVQFN\tRHB\t32\tLevel-2-260C-1_YEAR\n";
}

void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links);
void insertOrUpdatePackages(sqlite3 *db, ifstream &packages);

const string INSERT_DEVICE = "INSERT INTO device (datasheet_id,model,freq_max,storage_bytes,"
							 "ram_bytes,gpio_count,uart_count,usb_count,i2c_count,spi_count,"
							 "comp_count,timer_count,op_temp_min,op_temp_max,comment) VALUES ";

int main(int argc, char **argv) // opties voor elke .txt file? misschien niet slecht?
{
	// const char *families = nullptr;
	// const char *datasheets = nullptr;
	// const char *links = nullptr;
	// const char *packages = nullptr;
	ifstream families, links, packages;
	const char *database = nullptr;

	int opt;
	while ( (opt = getopt(argc, argv, "d:f:l:p:h")) != -1 ) {
		switch ( opt ) {
			// case 'd':
			// 	datasheets = optarg;
			// 	break;
			case 'f':
				families.open(optarg);
				break;
			case 'l':
				links.open(optarg);
				break;
			case 'p':
				packages.open(optarg);
				break;
			case 'h':
			default:
				printUsage();
				return EX_USAGE;
		}
	}
	if ( argc > optind ) {
		database = argv[optind];
	} else {
		printUsage();
		return EX_USAGE;
	}

	sqlite3 *sql;
	// sqlite3_open("file::memory:", &sql);
	cout << "Opening SQLite3 database " << database << endl;

	unsigned int rc = sqlite3_open(database, &sql);
	if ( rc != 0 ) {
		sqlite3_close(sql);
		return 1;
	}

	// datasheets have been imported manually already

	// read msp430-family.txt for devices (export van TI website! niet modificeren)
	// read packages.txt (extracted from datasheets)
	// extend packages.txt? niet ieder DS heeft devices in header; meeste wel
	//  - mogelijk: proberen, indien 1 optie: OK, anders vragen?
	//  - of beter?: lijst van links, die resolutie zou 99% ok moeten zijn op dit moment
	//      - wiel niet opnieuw uitvinden, maar geen manuele verificatie op deze manier?
	// MAAR: zitten toch nog altijd met de matching van mcu & package
	// EN: niet elke match is op naam te doen!
	// OPLOSSING: derde txt file aangemaakt met device & datasheet
	if ( families.is_open() && links.is_open() ) {
		insertOrUpdateFamilies(sql, families, links);
	} else {
		cout << "No families & links read " << endl;
	}

	if ( packages.is_open() ) {
		insertOrUpdatePackages(sql, packages);
	} else {
		cout << "No packages read" << endl;
	}

	sqlite3_close(sql);
	return 0;
}

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

void addGroupFeatures(vector<string> &features, const string &part, const string &text, const string &group, const string &param1 = "",
					  const string &param2 = "", const string &param3 = "") {
	if ( text.empty() || group.empty() ) {
		return;
	}
	// comma-separated values ... select using IN-statement
	static const string QUERY = "SELECT id "
								"FROM feature "
								"WHERE family_group = '"
							  + group + "' AND family_text IN (";
	static const string INSERT_QUERY = "INSERT INTO device_feature (device_id,feature_id,param1,param2,param3,comment) "
									   "VALUES ( SELECT id FROM device WHERE model = ";

	// select from DB features table
	string select = QUERY;
	addStringsIn(select, text);
	select += ");";
	features.push_back(select); // TEMP REMOVE once db accessed

	// for
	{
		string insert = INSERT_QUERY;
		addNextString(insert, part);
		addNextString(insert, group); // TODO from for
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
	vector<string> featureLinks;
	// no, this isn't efficient, but it's fine for this program
	string query;
	// first line contains header, but no datasheet will be found anyway
	while ( getline(families, line) ) {
		featureLinks.clear();
		tab1 = 0;

		query = INSERT_DEVICE;
		query.append("( ");

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
		// Number of ADC channels
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(featureLinks, part, adc, "ADC", value);

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
		addGroupFeatures(featureLinks, part, value, "BSL");

		// Special I/O
		// TODO: features
		value = nextTSV(line, tab1, tab2);
		addGroupFeatures(featureLinks, part, value, "Special I/O");

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
		addGroupFeatures(featureLinks, part, value, "Features");

		addNextString(query, "AUTOMATIC RESOLUTION");

		// insert or update in device table
		// comment: TI EXPORT
		query[query.length() - 1] = ')';
		cout << query << endl;
		for ( string &q : featureLinks ) {
			cout << q << endl;
		}
	}
}

void insertOrUpdatePackages(sqlite3 *db, ifstream &packages) {
	// for packages
	{
		// insert package & use datasheet to resolve family + part
		// comment: AUTOMATIC RESOLUTION (!= MANUALLY VERIFIED)
	}
}
