#ifndef MYLIBRARY_TI_MSP430F2001_HPP_
#define MYLIBRARY_TI_MSP430F2001_HPP_

//#include "msp430f2001.h"

#include "../generic.hpp"

#include "msp430/gpio-port.hpp"
#include "msp430/gpio-pin.hpp"
#include "msp430/registers.hpp"

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
    GPIO2_6 = BIT6,
    GPIO2_7 = BIT7
};

typedef GpioTemplate<P1IN, P1OUT, P1DIR, P1IFG, P1IES, P1IE, P1SEL, P1REN, Gpio1Pins> t_gpio1;
typedef GpioTemplate<P2IN, P2OUT, P2DIR, P2IFG, P2IES, P2IE, P2SEL, P2REN, Gpio2Pins> t_gpio2;

const t_gpio1 gpio1;
const t_gpio2 gpio2;
}

#endif /* MYLIBRARY_TI_MSP430FR2433_HPP_ */
