#include <iostream>

#include "elevator/Panel.h"

class PressedState : public IButtonState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Pressed";
        return os;
    }    
};

class ReleasedState : public IButtonState {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Released";
        return os;
    }    
};

class UpButton : public IButton {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Up Button";
        return os;
    }
};

class DownButton : public IButton {
public:
    std::ostream& Printout(std::ostream& os) const override {
        os << "Down Button";
        return os;
    }
};

static const IButtonState* PRESSED_STATE = new PressedState();
static const IButtonState* RELEASED_STATE = new ReleasedState();

static const IButton* UP_BUTTON = new UpButton();
static const IButton* DOWN_BUTTON = new DownButton();

class Panel : public IPanel {
    private:
    IButtonState* downButtonState;
    IButtonState* upButtonState;

    IButton* downButton;
    IButton* upButton;

    public:
    Panel() 
        : downButtonState((IButtonState*)RELEASED_STATE), upButtonState((IButtonState*)RELEASED_STATE),
          downButton((IButton*)DOWN_BUTTON), upButton((IButton*)UP_BUTTON) {}

    ~Panel() {}

    Panel(const Panel& other) 
        : downButtonState(other.downButtonState), upButtonState(other.upButtonState),
          downButton(other.downButton), upButton(other.upButton) {}

    Panel& operator=(const Panel& other) {
        if (this != &other) {
            downButtonState = other.downButtonState;
            upButtonState = other.upButtonState;
            downButton = other.downButton;
            upButton = other.upButton;
        }
        return *this;
    }

    Panel(Panel&& other) noexcept
        : downButtonState(other.downButtonState), upButtonState(other.upButtonState),
          downButton(other.downButton), upButton(other.upButton) {}

    Panel& operator=(Panel&& other) noexcept {
        if (this != &other) {
            downButtonState = other.downButtonState;
            upButtonState = other.upButtonState;
            downButton = other.downButton;
            upButton = other.upButton;
        }
        return *this;
    }

    IButtonState* PressDownButton() {
        downButtonState = (IButtonState*)PRESSED_STATE;
        return downButtonState;
    };

    IButtonState* ReleaseDownButton() {
        downButtonState = (IButtonState*)RELEASED_STATE;
        return downButtonState;
    };

    IButtonState* PressUpButton() {
        upButtonState = (IButtonState*)PRESSED_STATE;
        return upButtonState;
    }

    IButtonState* ReleaseUpButton() {
        upButtonState = (IButtonState*)RELEASED_STATE;
        return upButtonState;
    }
};