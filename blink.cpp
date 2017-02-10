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
//#include "msp430g2553.h"

using namespace mylibrary;

template<typename PIN>
class Led: PIN {
public:
    void on() {
        PIN::toggle();
    }

    void off() {
        PIN::toggle();
    }
};

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    Led<Pin<P1IN, P1OUT, P1DIR, P1IFG, P1IES, P1IE, P1SEL, P1REN, Gpio1Pins, GPIO1_6> > led;
    led.on();

    const Pin<P1IN, P1OUT, P1DIR, P1IFG, P1IES, P1IE, P1SEL, P1REN, Gpio1Pins, GPIO1_6> greenLed = p1_6;

    greenLed.configureAsOutput();
    p1_6.configureAsOutput();

    p1_3.configureAsInput();

    unsigned int rounds = 0;
    for (;;) {
        while (p1_3.isLow()) {
        }
        p1_0.toggle();

        while (p1_3.isHigh()) {
        }
        p1_6.toggle();
        rounds++;
    }

    return 0;
}
