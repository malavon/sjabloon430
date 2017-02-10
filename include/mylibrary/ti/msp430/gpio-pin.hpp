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

    void toggle() const {
        GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::toggle(pin);
    }

    bool isLow() const {
        return GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::isLow(pin);
    }

    bool isHigh() const {
        return GpioTemplate<inReg, outReg, dirReg, intReg, intEdgeReg, intEnReg, selectReg, resistorReg, P>::isHigh(pin);
    }
private:
//    Pin(const Pin& src);
//    Pin& operator=(const Pin& src);
};

}

#endif /* MYLIBRARY_TI_MSP430_GPIO_PIN_HPP_ */
