#include <iostream>

#include "sqlite3.h"

using namespace std;

int main()
{
    // do in-memory or preferrably in a transaction if possible
    // store dumb, filtering possible in pure SQL (no globs etc - maybe useful for reference though)

    cout << "Datasheet (slas...)? " << endl; // or argument/option if present?
    // misschien geen keuze laten, devices/package moet al bestaan???
    cout << "Parts? " << endl; // can be pre-filled already?
    cout << "Package drawing n" << endl; // can be pre-filled already? list exists
    // keep adding packages until empty
    { // while (all pins empty)
        // for: packages
        // <PKG> outlined with spaces to longest package
        cout << "<PKG> Pin? " << endl; // pin can be empty for ease-of-use
        {
            // autocomplete from DB, tab for completion? enter ok?
            cout << "Signal? (default) " << endl;
            // * means filter for certain packages: glob (e.g. msp430fr235x -> msp430fr235?)
            // glob can be negative too using !; show (IN: included - green? EX: excluded - red?) packages afterwards!
            // ** means double filter? might be useful to do for each asterisk
            cout << "Type? " << endl; // autocomplete from DB when known
            // keep asking for signal (default only once) until empty
        }
    }

    // in db, not asked? might be useful, but show default first (e.g. GPIO_P_INT instead of GPIO?):
    // family (GPIO_PU, GPIO_P_INT, ADC ...)
    // human-readable name: GPIO Port x, IO y (PU/PD/INT); ADC Analog Input x ...
    // features from tsv file first: ADC10/ADC12 etc
    return 0;
}
