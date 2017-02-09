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

using namespace mylibrary;

template<typename PIN>
class Led: private PIN {
public:
    Led() {
        PIN::configureAsOutput();
    }

    void on() const {
        PIN::setHigh();
    }

    void off() const {
        PIN::setLow();
    }

    void toggle() const {
        PIN::toggle();
    }
};


template<typename PIN>
class Button: private PIN {
public:
    Button() {
        PIN::configureAsInput();
    }

    bool isPressed() const {
        return PIN::isHigh();
    }

    bool isReleased() const {
        return PIN::isLow();
    }
};


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

	const Led<decltype(p1_0)> greenLed;
    const Led<decltype(p1_6)> redLed;
    const Button<decltype(p1_3)> button;
    redLed.off();
    greenLed.off();

    unsigned int rounds = 0;
    for (;;) {
        while (button.isReleased()) {
        }
        greenLed.toggle();

        while (button.isPressed()) {
        }
        redLed.toggle();
        rounds++;
    }

    return 0;
}
