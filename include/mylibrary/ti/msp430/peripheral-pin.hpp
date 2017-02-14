#ifndef INCLUDE_MYLIBRARY_TI_MSP430_PERIPHERAL_PIN_HPP_
#define INCLUDE_MYLIBRARY_TI_MSP430_PERIPHERAL_PIN_HPP_

#include "mylibrary/types.hpp"
#include "mylibrary/gpio.hpp"

namespace mylibrary {

template<int>
class __dummyConfiguration {
};

template<typename CONFIGURER, typename GPIO_PIN>
class GpioConfigurable: private CONFIGURER {
public:
    GPIO_PIN asGpioPin() const {
        CONFIGURER::configureAsGpio();
        return GPIO_PIN();
    }

    ActiveHighOutput<GPIO_PIN> asOutputActiveHigh(bool autoConfigure = true) const {
        return ActiveHighOutput<GPIO_PIN>(autoConfigure);
    }

    ActiveLowOutput<GPIO_PIN> asOutputActiveLow(bool autoConfigure = true) const {
        return ActiveLowOutput<GPIO_PIN>(autoConfigure);
    }

    ActiveHighInput<GPIO_PIN> asInputActiveHigh(bool autoConfigure = true) const {
        return ActiveHighInput<GPIO_PIN>(autoConfigure);
    }

    ActiveLowInput<GPIO_PIN> asInputActiveLow(bool autoConfigure = true) const {
        return ActiveLowInput<GPIO_PIN>(autoConfigure);
    }
};

//template<>
class TimerAConfigurable {
    void asTimerPin() const {
//            return TimerPeripheralPin();
    }
};

class AnalogClockConfigurable {
};

class ADC10InputConfigurable {
};

class ComparatorInputConfigurable {
};

template<typename CONF1, typename CONF2 = __dummyConfiguration <2>, typename CONF3 = __dummyConfiguration <3>, typename CONF4 = __dummyConfiguration <4>, typename CONF5 = __dummyConfiguration <5> >
class PeripheralPin: public CONF1, public CONF2, public CONF3, public CONF4, public CONF5 {
public:
    PeripheralPin<CONF1, CONF2, CONF3, CONF4, CONF5>() :
            CONF1(), CONF2(), CONF3(), CONF4(), CONF5() {
    }
};

class PinConfigurer {
protected:
    void configureAsGpio() const;
};

template<vub& pinSelect1, vub& pinSelect2, const ub bit>
class Msp430G2xxxPinConfigurer: PinConfigurer {
protected:
    void configureAsGpio() const {
        pinSelect1 &= ~bit;
        pinSelect2 &= ~bit;
        // TODO: clear other registers as well!
    }
};
}
#endif /* INCLUDE_MYLIBRARY_TI_MSP430_PERIPHERAL_PIN_HPP_ */
