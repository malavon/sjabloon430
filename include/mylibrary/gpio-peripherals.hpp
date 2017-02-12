#ifndef INCLUDE_MYLIBRARY_GPIO_PERIPHERALS_HPP_
#define INCLUDE_MYLIBRARY_GPIO_PERIPHERALS_HPP_

#include "gpio.hpp"

namespace mylibrary {

template<typename OUTPUT>
class Led: private OUTPUT {
public:
    Led(bool autoConfigure = true) :
            OUTPUT(autoConfigure) {
    }

    void on() const {
        OUTPUT::active();
    }

    void off() const {
        OUTPUT::inactive();
    }

    void toggle() const {
        OUTPUT::toggle();
    }

    void disablePullUpDown() const {
        OUTPUT::disablePullUpDown();
    }

    void enablePullDown() const {
        OUTPUT::enablePullDown();
    }

    void enablePullUp() const {
        OUTPUT::enablePullUp();
    }
};

template<typename INPUT>
class Button: public INPUT {
public:
    Button(bool autoConfigure = true) :
            INPUT(autoConfigure) {
    }

    bool isPressed() const {
        return INPUT::isActive();
    }

    bool isReleased() const {
        return INPUT::isInactive();
    }

    void disablePullUpDown() const {
        INPUT::disablePullUpDown();
    }

    void enablePullDown() const {
        INPUT::enablePullDown();
    }

    void enablePullUp() const {
        INPUT::enablePullUp();
    }

};

}
#endif /* INCLUDE_MYLIBRARY_GPIO_PERIPHERALS_HPP_ */
