#include <getopt.h>
#include <sysexits.h>

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "sqlite3.h"

using namespace std;

void printUsage() {
	cout << "Usage: devices [-h] "
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
	cout << "argc " << argc << " & optind " << optind << endl;
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

void addNextString(string &query, string value) {
	query.push_back('\'');
	query.append(value);
	query.push_back('\'');
	query.push_back(',');
}

void addNextInteger(string &query, string value) {
	// no quotes, numbers are simply inserted (even though they are floating-point)
	query.append(value.empty() ? "0" : value);
	query.push_back(',');
}

string nextTSV(string &line, unsigned int &tab1, unsigned int &tab2) {
	unsigned int temp = tab1;
	tab2 = line.find('\t', tab1);
	tab1 = tab2 + 1;
	return line.substr(temp, tab2 - temp);
}

void insertOrUpdateFamilies(sqlite3 *db, ifstream &families, ifstream &links) {
	string line;
	// read links in map first

	unordered_map<string, string> datasheets;
	while ( getline(links, line) ) {
		// expected <device>\t<datasheet>
		// e.g. MSP430FR2533	SLAS942
		// abuse the fact that datasheets are always 7 characters long
		// preceded by a single character (tab)
		unsigned int l = line.length();
		datasheets[line.substr(0, l - 8)] = line.substr(l - 7);
		// cout << "datasheet '" << line.substr(l - 7) << "' for device '" << line.substr(0, l - 8) << "'" << endl;
	}

	unsigned int tab1, tab2;
	string value;
	// no, this isn't efficient, but it's fine for this program
	string query;
	// first line contains header, but no datasheet will be found anyway
	while ( getline(families, line) ) {
		tab1 = 0;
		query = INSERT_DEVICE;
		query.append("( ");

		// Part & Datasheet!!
		value = nextTSV(line, tab1, tab2);
		// if NULL, should fail
		addNextString(query, datasheets[value]);
		addNextString(query, value);
		// tab1 = line.find('\t', 0);
		// query.append("( \"");
		// query.append(line.substr(0, tab1));
		// query.push_back('"');

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
		nextTSV(line, tab1, tab2);
		// TODO: interpret & add features
		// Number of ADC channels
		nextTSV(line, tab1, tab2);

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
		nextTSV(line, tab1, tab2);
		// Special I/O
		// TODO: features
		nextTSV(line, tab1, tab2);

		// Operating temperature range (°C)
		// (-)n(n) to mm(m)
		value = nextTSV(line, tab1, tab2);
		tab2 = value.find(" to ");
		addNextInteger(query, value.substr(0, tab2));
		addNextInteger(query, value.substr(tab2 + 4, value.length() - tab2 - 4));

		// Price|Quantity (USD)	Package type	Pin count	Package area (mm^2)	Package
		// size (L x W) (mm)	Features

		addNextString(query, "AUTOMATIC RESOLUTION");

		// insert or update in device table
		// comment: TI EXPORT
		query[query.length() - 1] = ')';
		cout << query << endl;
	}
}

void insertOrUpdatePackages(sqlite3 *db, ifstream &packages) {
	// for packages
	{
		// insert package & use datasheet to resolve family + part
		// comment: AUTOMATIC RESOLUTION (!= MANUALLY VERIFIED)
	}
}
