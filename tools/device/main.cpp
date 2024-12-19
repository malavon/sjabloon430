#include <getopt.h>

#include <iostream>

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

int main() // opties voor elke .txt file? misschien niet slecht?
{
	printUsage();
	// sqlite3 *sql;
	// read msp430-family.txt for devices (export van TI website! niet modificeren)
	// read packages.txt (extracted from datasheets)
	// extend packages.txt? niet ieder DS heeft devices in header; meeste wel
	//  - mogelijk: proberen, indien 1 optie: OK, anders vragen?
	//  - of beter?: lijst van links, die resolutie zou 99% ok moeten zijn op dit moment
	//      - wiel niet opnieuw uitvinden, maar geen manuele verificatie op deze manier?
	// MAAR: zitten toch nog altijd met de matching van mcu & package
	// EN: niet elke match is op naam te doen!
	// OPLOSSING: derde txt file aangemaakt met device & datasheet
	// for family
	{
		// insert or update in device table
		// comment: TI EXPORT
	}
	// for datasheet links
	{
		// insert or update in device table
		// comment: AUTOMATIC RESOLUTION (!= MANUALLY VERIFIED)
	}
	// for datasheets (rev & dates)
	{
		// insert (or update?) in device table
	}
	// for packages
	{
		// insert package & use datasheet to resolve family + part
		// comment: AUTOMATIC RESOLUTION (!= MANUALLY VERIFIED)
	}

	// sqlite3_close(sql);
	return 0;
}
