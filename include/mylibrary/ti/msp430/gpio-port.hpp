#ifndef MYLIBRARY_TI_GPIOT_H_
#define MYLIBRARY_TI_GPIOT_H_

#include "../includes.h"

namespace mylibrary {

template<vub& dirReg, class P>
class GpioConf;

template<vub& outReg, class P>
class GpioToggle;

template<vub& inReg, vub& outReg, vub& dirReg, vub& intReg, vub& intEdgeReg, vub& intEnReg, vub& selectReg, vub& resistorReg, class P>
class GpioTemplate: public GpioConf<dirReg, P>, public GpioToggle<outReg, P> {
public:
    GpioTemplate() {
    }

    bool isLow(const P pin) const {
        return inReg & pin == 0;
    }

    bool isHigh(const P pin) const {
        return inReg & pin == pin;
    }

private:
//    GpioTemplate(const GpioTemplate& srcMyClass);
    GpioTemplate& operator=(const GpioTemplate& srcMyClass);
};

// don't like these at all, but how can I make this nicer without exploding code size? :(

template<vub& dirReg, class P>
class GpioConf {
public:
    void configureAsInput(const P pin1) const {
        configureAsInputInternal((b) pin1);
    }

    void configureAsInput(const P pin1, const P pin2) const {
        configureAsInputInternal(pin1 | pin2);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3) const {
        configureAsInputInternal(pin1 | pin2 | pin3);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3, const P pin4) const {
        configureAsInputInternal(pin1 | pin2 | pin3 | pin4);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5) const {
        configureAsInputInternal(pin1 | pin2 | pin3 | pin4 | pin5);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6) const {
        configureAsInputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7) const {
        configureAsInputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7);
    }

    void configureAsInput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7, const P pin8) const {
        configureAsInputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

    void configureAsOutput(const P pin1) const {
        configureAsOutputInternal((b) pin1);
    }

    void configureAsOutput(const P pin1, const P pin2) const {
        configureAsOutputInternal(pin1 | pin2);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3) const {
        configureAsOutputInternal(pin1 | pin2 | pin3);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3, const P pin4) const {
        configureAsOutputInternal(pin1 | pin2 | pin3 | pin4);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5) const {
        configureAsOutputInternal(pin1 | pin2 | pin3 | pin4 | pin5);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6) const {
        configureAsOutputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7) const {
        configureAsOutputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7);
    }

    void configureAsOutput(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7, const P pin8) const {
        configureAsOutputInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

protected:
    static void configureAsInputInternal(b pins) {
        dirReg &= ~pins;
    }

    static void configureAsOutputInternal(b pins) {
        dirReg |= pins;
    }

//    template<typename PORT, uint16_t pin>
//    friend class Pin;
};

template<vub& outReg, class P>
class GpioToggle {
public:
    static void toggle(const P pin1) {
        toggleInternal((b) pin1);
    }

    void toggleInternal(const P pin1, const P pin2) {
        toggleInternal(pin1 | pin2);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3) {
        toggleInternal(pin1 | pin2 | pin3);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3, const P pin4) {
        toggleInternal(pin1 | pin2 | pin3 | pin4);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5) {
        toggleInternal(pin1 | pin2 | pin3 | pin4 | pin5);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6) {
        toggleInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7) {
        toggleInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7);
    }

    void toggleInternal(const P pin1, const P pin2, const P pin3, const P pin4, const P pin5, const P pin6, const P pin7, const P pin8) {
        toggleInternal(pin1 | pin2 | pin3 | pin4 | pin5 | pin6 | pin7 | pin8);
    }

protected:
    static void toggleInternal(const b pins) {
        outReg ^= pins;
    }
};

} // namespace mylibrary
#endif /* MYLIBRARY_TI_GPIOT_H_ */
