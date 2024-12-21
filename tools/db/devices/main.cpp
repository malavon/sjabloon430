#include <getopt.h>
#include <sysexits.h>

#include <fstream>
#include <iostream>

#include "sqlite3.h"

using namespace std;

void printUsage() {
	cout << "Usage: devices [-h] "
		 // << "[-d <datasheets-file>] "
		 << "[-f <families-file>] "
		 << "[-l <links-file>] "
		 << "[-p <packages-file>] <sqlite3db>" << endl;

	cout << "<families-file> is a SORTED tab-separated file exported from the TI website "
			"and converted to tsv containing records of:\n"
		 << "\tPart\tFrequency\tNonvolatile Memory\tRAM\tADC Type etc\n\n";

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

void insertOrUpdateFamilies(sqlite3 *db, const ifstream &families, const ifstream &links);
void insertOrUpdatePackages(sqlite3 *db, const ifstream &packages);

const string INSERT_DEVICE = "INSERT INTO device (datasheet_id,model,freq_max,storage_bytes,"
							 "ram_bytes,gpio_count,uart_count,usb_count,i2c_count,spi_count,"
							 "timer_count,op_temp_min,op_temp_max,comment) VALUES";

int main(int argc, char **argv) // opties voor elke .txt file? misschien niet slecht?
{
	// const char *families = nullptr;
	// const char *datasheets = nullptr;
	// const char *links = nullptr;
	// const char *packages = nullptr;
	ifstream families, links, packages;
	const char *database = nullptr;

	int opt;
	while ( (opt = getopt(argc, argv, "dflph")) != -1 ) {
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

	if ( argc > optind + 1 ) {
		database = argv[optind + 1];
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
		cout << "Could not read ";
		if ( !families.is_open() ) {
			cout << "families ";
			if ( links.is_open() ) {
				cout << "file ";
			} else {
				cout << "and links files";
			}
			cout << endl;
			return EX_DATAERR;
		}
	}

	if ( packages.is_open() ) {
		insertOrUpdatePackages(sql, packages);
	} else {
		cout << "Could not read packages file" << endl;
		return EX_DATAERR;
	}

	sqlite3_close(sql);
	return 0;
}

void insertOrUpdateFamilies(sqlite3 *db, const ifstream &families, const ifstream &links) {
	// for family
	{
		// insert or update in device table
		// comment: TI EXPORT
	}
}

void insertOrUpdatePackages(sqlite3 *db, const ifstream &packages) {
	// for packages
	{
		// insert package & use datasheet to resolve family + part
		// comment: AUTOMATIC RESOLUTION (!= MANUALLY VERIFIED)
	}
}
