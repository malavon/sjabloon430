#ifndef INCLUDE_MYLIBRARY_GPIO_HPP_
#define INCLUDE_MYLIBRARY_GPIO_HPP_

namespace mylibrary {

template<typename PIN>
class Output: protected PIN {
protected:
    Output(bool autoConfigure = true) {
        if (autoConfigure) {
            PIN::configureAsOutput();
        }
    }

public:
    void toggle() const {
        PIN::toggle();
    }

    void disablePullUpDown() const {
        PIN::disablePullUpDown();
    }

    void enablePullDown() const {
        PIN::enablePullDown();
    }

    void enablePullUp() const {
        PIN::enablePullUp();
    }
};

template<typename PIN>
class ActiveHighOutput: public Output<PIN> {
public:
    ActiveHighOutput(bool autoConfigure = true) :
            Output<PIN>(autoConfigure) {
    }

public:
    void active() const {
        PIN::setHigh();
    }

    void inactive() const {
        PIN::setLow();
    }
};

template<typename PIN>
class ActiveLowOutput: public Output<PIN> {
public:
    ActiveLowOutput(bool autoConfigure = true) :
            Output<PIN>(autoConfigure) {
    }

public:
    void active() const {
        PIN::setLow();
    }

    void inactive() const {
        PIN::setHigh();
    }
};

template<typename PIN>
class Input: protected PIN {
protected:
    Input(bool autoConfigure = true) {
        if (autoConfigure) {
            PIN::configureAsInput();
        }
    }

public:
    void disablePullUpDown() const {
        PIN::disablePullUpDown();
    }

    void enablePullDown() const {
        PIN::enablePullDown();
    }

    void enablePullUp() const {
        PIN::enablePullUp();
    }
};

template<typename PIN>
class ActiveHighInput: public Input<PIN> {
public:
    ActiveHighInput(bool autoConfigure = true) :
            Input<PIN>(autoConfigure) {
    }

public:
    bool isActive() const {
        return PIN::isHigh();
    }

    bool isInactive() const {
        return PIN::isLow();
    }
};

template<typename PIN>
class ActiveLowInput: public Input<PIN> {
public:
    ActiveLowInput(bool autoConfigure = true) :
            Input<PIN>(autoConfigure) {
    }

public:
    bool isActive() const {
        return PIN::isLow();
    }

    bool isInactive() const {
        return PIN::isHigh();
    }
};

}
#endif /* INCLUDE_MYLIBRARY_GPIO_HPP_ */
