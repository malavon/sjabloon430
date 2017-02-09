#ifndef MYLIBRARY_TI_GPIOT_H_
#define MYLIBRARY_TI_GPIOT_H_

#include "../includes.h"

namespace mylibrary {
template<vub& inReg, vub& outReg, vub& dirReg, vub& intReg, vub& intEdgeReg, vub& intEnReg, vub& selectReg, vub& resistorReg, class P>
class GpioTemplate {
public:
    GpioTemplate() {
    }

    void configureAsInput(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0,
            const P pin8 = (P) 0) const {
        dirReg &= ~(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void configureAsOutput(const P pin1, const P pin2 = (P) 0, const P pin3 = (P) 0, const P pin4 = (P) 0, const P pin5 = (P) 0, const P pin6 = (P) 0, const P pin7 = (P) 0,
            const P pin8 = (P) 0) const {
        dirReg |= (pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    bool isLow(const P pin) const {
        return inReg & pin == 0;
    }

    bool isHigh(const P pin) const {
        return inReg & pin == pin;
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

} // namespace mylibrary
#endif /* MYLIBRARY_TI_GPIOT_H_ */
