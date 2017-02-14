#ifndef MYLIBRARY_TI_MSP430G2553IN20_HPP_
#define MYLIBRARY_TI_MSP430G2553IN20_HPP_

#include "mylibrary/ti/msp430g2553.hpp"

namespace mylibrary {

const PeripheralPin<GpioConfigurable<Config<BIT0>, gp1_0_t>, TimerAConfigurable, AnalogClockConfigurable, ADC10InputConfigurable, ComparatorInputConfigurable> pp02;
const PeripheralPin<GpioConfigurable<Config<BIT1>, gp1_1_t> > pp03;
const PeripheralPin<GpioConfigurable<Config<BIT2>, gp1_2_t> > pp04;
const PeripheralPin<GpioConfigurable<Config<BIT3>, gp1_3_t> > pp05;
const PeripheralPin<GpioConfigurable<Config<BIT4>, gp1_4_t> > pp06;
const PeripheralPin<GpioConfigurable<Config<BIT5>, gp1_5_t> > pp07;
const PeripheralPin<GpioConfigurable<Config<BIT0>, gp2_0_t> > pp08;
const PeripheralPin<GpioConfigurable<Config<BIT1>, gp2_1_t> > pp09;
const PeripheralPin<GpioConfigurable<Config<BIT2>, gp2_2_t> > pp10;

const PeripheralPin<GpioConfigurable<Config<BIT3>, gp2_3_t> > pp11;
const PeripheralPin<GpioConfigurable<Config<BIT4>, gp2_4_t> > pp12;
const PeripheralPin<GpioConfigurable<Config<BIT5>, gp2_5_t> > pp13;
const PeripheralPin<GpioConfigurable<Config<BIT6>, gp1_6_t> > pp14;
const PeripheralPin<GpioConfigurable<Config<BIT7>, gp1_7_t> > pp15;
//const PeripheralPin<GpioConfigurable<Config<BITx>,> > pp16;
//const PeripheralPin<GpioConfigurable<Config<BITx>,> > pp17;
const PeripheralPin<GpioConfigurable<Config<BIT7>, gp2_7_t> > pp18;
const PeripheralPin<GpioConfigurable<Config<BIT6>, gp2_6_t> > pp19;

class Mcu {
public:
    Mcu() {
    }

    void safeInit() const {
        gpio1.safeInit();
        gpio2.safeInit();
    }
};

const Mcu mcu;
}

#endif /* MYLIBRARY_TI_MSP430G2553IN20_HPP_ */
