#ifndef MYLIBRARY_TI_MSP430F2001_HPP_
#define MYLIBRARY_TI_MSP430F2001_HPP_

#include "msp430g2553.h"

#include "../compat.hpp"
#include "msp430/gpio-port.hpp"
#include "msp430/gpio-pin.hpp"

#include "msp430/peripheral-pin.hpp"

/*
 After a system reset, user software must initialize the device for the application requirements. The
 following must occur:
 • Initialize the stack pointer (SP), typically to the top of RAM.
 • Initialize the watchdog to the requirements of the application.
 • Configure peripheral modules to the requirements of the application.
 */

namespace mylibrary {

enum Gpio1Pins {
    GPIO1_0 = BIT0,
    GPIO1_1 = BIT1,
    GPIO1_2 = BIT2,
    GPIO1_3 = BIT3,
    GPIO1_4 = BIT4,
    GPIO1_5 = BIT5,
    GPIO1_6 = BIT6,
    GPIO1_7 = BIT7
};

enum Gpio2Pins {
    GPIO2_0 = BIT0,
    GPIO2_1 = BIT1,
    GPIO2_2 = BIT2,
    GPIO2_3 = BIT3,
    GPIO2_4 = BIT4,
    GPIO2_5 = BIT5,
    GPIO2_6 = BIT6,
    GPIO2_7 = BIT7
};

// P3: 0-7 for 28-pin devices, no interrupt capability

const GpioPortWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins> gpio1;
const GpioPortWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins> gpio2;

typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_0> gp1_0_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_1> gp1_1_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_2> gp1_2_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_3> gp1_3_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_4> gp1_4_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_5> gp1_5_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_6> gp1_6_t;
typedef PinWithInterrupt<P1IN, P1OUT, P1DIR, P1REN, P1IFG, P1IES, P1IE, Gpio1Pins, GPIO1_7> gp1_7_t;

typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_0> gp2_0_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_1> gp2_1_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_2> gp2_2_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_3> gp2_3_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_4> gp2_4_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_5> gp2_5_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_6> gp2_6_t;
typedef PinWithInterrupt<P2IN, P2OUT, P2DIR, P2REN, P2IFG, P2IES, P2IE, Gpio2Pins, GPIO2_7> gp2_7_t;

template<ub bit>
class Config: protected Msp430G2xxxPinConfigurer<P1SEL, P1SEL2, bit> {
};

}
#endif /* MYLIBRARY_TI_MSP430FR2433_HPP_ */
