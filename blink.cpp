//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include "mylibrary/ti/msp430g2553.hpp"
#include "mylibrary/gpio-peripherals.hpp"

using namespace mylibrary;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    mcu.safeInit();

    const Led<OutputActiveHigh<p1_0_t> > redLed;
    const Led<OutputActiveHigh<p1_6_t> > greenLed;
    const Button<InputActiveLow<p1_3_t> > button;

    button.enablePullUp();

    for (;;) {
        while (button.isReleased()) {
        }
        greenLed.on();
        redLed.off();

        while (button.isReleased()) {
        }
        greenLed.off();
        redLed.on();
    }

    return 0;
}
