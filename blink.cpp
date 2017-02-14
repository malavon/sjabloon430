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

#include "mylibrary/ti/msp430g2553in20.hpp"
#include "mylibrary/gpio-peripherals.hpp"

using namespace mylibrary;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    mcu.safeInit();

    const Led<ActiveHighOutput<gp1_0_t> > redLed(pp02.asOutputActiveHigh());
    const Led<ActiveHighOutput<gp1_6_t> > greenLed(pp14.asOutputActiveHigh());
    const Button<ActiveLowInput<gp1_3_t> > button(pp05.asInputActiveLow());

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
