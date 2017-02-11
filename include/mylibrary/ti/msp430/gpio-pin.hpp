#ifndef MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_
#define MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_

#include "gpio-port.hpp"

namespace mylibrary {

template<vub& inReg, vub& outReg, vub& dirReg, vub& selectReg, vub& resistorReg, class P, const P pin>
class Pin: private GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P> {
public:
    Pin() {
    }

    void configureAsInput() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::configureAsInput(pin);
    }

    void configureAsOutput() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::configureAsOutput(pin);
    }

    void enablePulldown() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::enablePulldown(pin);
    }

    void enablePullup() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::enablePullup(pin);
    }

    bool isLow() const {
        return GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::isLow(pin);
    }

    bool isHigh() const {
        return GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::isHigh(pin);
    }

    void setLow() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::setLow(pin);
    }

    void setHigh() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::setHigh(pin);
    }

    void toggle() const {
        GpioPort<inReg, outReg, dirReg, selectReg, resistorReg, P>::toggle(pin);
    }
};

template<vub& inReg, vub& outReg, vub& dirReg, vub& selectReg, vub& resistorReg, vub& intReg, vub& intEdgeReg, vub& intEnReg, class P, const P pin>
class PinWithInterrupt: public Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>, private GpioPortWithInterrupt<inReg, outReg, dirReg, selectReg, resistorReg, intReg, intEdgeReg, intEnReg, P> {
public:
    PinWithInterrupt() {
    }

    // these methods need to be here to resolve ambiguity
    void configureAsInput() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::configureAsInput();
    }

    void configureAsOutput() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::configureAsOutput();
    }

    void enablePulldown() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::enablePulldown();
    }

    void enablePullup() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::enablePullup();
    }

    bool isLow() const {
        return Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::isLow();
    }

    bool isHigh() const {
        return Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::isHigh();
    }

    void setLow() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::setLow();
    }

    void setHigh() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::setHigh();
    }

    void toggle() const {
        Pin<inReg, outReg, dirReg, selectReg, resistorReg, P, pin>::toggle();
    }
};

}


#endif /* MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_ */
