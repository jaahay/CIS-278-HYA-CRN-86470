#include <iostream>

#include "Panel.h"

class PressedState : public IButtonState {
    public:
    PressedState() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Pressed";
        return os;
    }    
};

class ReleasedState : public IButtonState {
    public:
    ReleasedState() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Released";
        return os;
    }    
};

class UpButton : public IButton {
    public:
    UpButton() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Up Button";
        return os;
    }
};

class DownButton : public IButton {
    public:
    DownButton() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Down Button";
        return os;
    }
};

static const IButtonState* PRESSED_STATE = new PressedState();
static const IButtonState* RELEASED_STATE = new ReleasedState();

static const IButton* UP_BUTTON = new UpButton();
static const IButton* DOWN_BUTTON = new DownButton();

class ElevatorPanel : public IPanel {
    private:
    IButtonState* downButtonState;
    IButtonState* upButtonState;

    IButton* downButton;
    IButton* upButton;

    public:
    ElevatorPanel() 
        : downButtonState((IButtonState*)RELEASED_STATE), upButtonState((IButtonState*)RELEASED_STATE),
          downButton((IButton*)DOWN_BUTTON), upButton((IButton*)UP_BUTTON) {}

    ~ElevatorPanel() {}

    ElevatorPanel(const ElevatorPanel& other) 
        : downButtonState(other.downButtonState), upButtonState(other.upButtonState),
          downButton(other.downButton), upButton(other.upButton) {}

    ElevatorPanel& operator=(const ElevatorPanel& other) {
        if (this != &other) {
            downButtonState = other.downButtonState;
            upButtonState = other.upButtonState;
            downButton = other.downButton;
            upButton = other.upButton;
        }
        return *this;
    }

    ElevatorPanel(ElevatorPanel&& other) noexcept
        : downButtonState(other.downButtonState), upButtonState(other.upButtonState),
          downButton(other.downButton), upButton(other.upButton) {}

    ElevatorPanel& operator=(ElevatorPanel&& other) noexcept {
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