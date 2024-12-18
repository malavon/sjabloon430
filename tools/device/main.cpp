#include <iostream>

using namespace std;

int main() // opties voor elke .txt file? misschien niet slecht?
{
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
    return 0;
}

