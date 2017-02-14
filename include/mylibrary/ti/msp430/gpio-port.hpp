#ifndef MYLIBRARY_TI_GPIOT_H_
#define MYLIBRARY_TI_GPIOT_H_

#include "mylibrary/types.hpp"

namespace mylibrary {

// todo second select regs
template<vub& inReg, vub& outReg, vub& dirReg, vub& resistorReg, class P>
class GpioPort {
public:
    GpioPort() {
    }

    void safeInit() const {
        /* We still force no output to prevent glitches, even though it's not necessary according to the text below.
         * This is done before selecting the direction, to prevent setting any pin to high.
         */
        outReg = 0x00;
        /*
         * Unused I/O pins should be configured as I/O function, output direction, and left unconnected on the PC
         * board, to prevent a floating input and reduce power consumption. The value of the PxOUT bit is irrelevant,
         * since the pin is unconnected. Alternatively, the integrated pullup/pulldown resistor can be enabled by
         * setting the PxREN bit of the unused pin to prevent the floating input. See the System Resets, Interrupts,
         * and Operating Modes chapter for termination of unused pins.
         */
        dirReg = 0xFF;
    }

    void configureAsInput(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0,
            const P pin8 = (P) 0) const {
        dirReg &= ~(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void configureAsOutput(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0,
            const P pin8 = (P) 0) const {
        dirReg |= (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void disablePullUpDown(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0,
            const P pin8 = (P) 0) const {
        // Bit = 0: Pullup/pulldown resistor disabled, Bit = 1: Pullup/pulldown resistor enabled
        resistorReg &= ~(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void enablePullDown(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        // Bit = 0: The pin is pulled down, Bit = 1: The pin is pulled up
        outReg |= ~(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
        // Bit = 0: Pullup/pulldown resistor disabled, Bit = 1: Pullup/pulldown resistor enabled
        resistorReg |= pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8;
    }

    void enablePullUp(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        // Bit = 0: The pin is pulled down, Bit = 1: The pin is pulled up
        outReg |= pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8;
        // Bit = 0: Pullup/pulldown resistor disabled, Bit = 1: Pullup/pulldown resistor enabled
        resistorReg |= pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8;
    }

    bool isLow(const P pin) const {
        return (inReg & pin) == 0;
    }

    bool isHigh(const P pin) const {
        return (inReg & pin) == pin;
    }

    bool areAllLow(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        return (inReg & (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8)) == 0;
    }

    bool areAllHigh(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        return (inReg & (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8)) == (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void setLow(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        outReg &= ~(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void setHigh(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        outReg |= pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8;
    }

    void toggle(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0, const P pin8 = (P) 0) const {
        outReg ^= (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }
};



template<vub& inReg, vub& outReg, vub& dirReg, vub& resistorReg, vub& intReg, vub& intEdgeReg, vub& intEnReg, class P>
class GpioPortWithInterrupt: public GpioPort<inReg, outReg, dirReg, resistorReg, P> {
public:
    GpioPortWithInterrupt() :
            GpioPort<inReg, outReg, dirReg, resistorReg, P>() {
    }

    // TODO: interrupt stuff
};

} // namespace mylibrary
#endif /* MYLIBRARY_TI_GPIOT_H_ */
