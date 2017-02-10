#ifndef MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_
#define MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_

#include "gpio-port.hpp"

namespace mylibrary {
template<vub& inReg, vub& outReg, vub& dirReg, vub& intReg, vub& intEdgeReg, vub& intEnReg, vub& selectReg, vub& resistorReg, class P, const P pin>
class Pin: private GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P> {
public:
    Pin() {
    }

    void configureAsInput() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::configureAsInput(pin);
    }

    void configureAsOutput() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::configureAsOutput(pin);
    }

    void enablePulldown() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::enablePulldown(pin);
    }

    void enablePullup() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::enablePullup(pin);
    }

    bool isLow() const {
        return GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::isLow(pin);
    }

    bool isHigh() const {
        return GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::isHigh(pin);
    }

    void setLow() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::setLow(pin);
    }

    void setHigh() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::setHigh(pin);
    }

    void toggle() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::toggle(pin);
    }
};
}

#endif /* MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_ */
