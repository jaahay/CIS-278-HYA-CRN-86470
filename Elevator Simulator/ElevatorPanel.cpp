#include <iostream>

#include "Panel.h"

class UpButton : public IButton {
    public:
    UpButton() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Up Button";
        return os;
    }
    std::string label() const override {
        return "Up";
    }    
};

class DownButton : public IButton {
    public:
    DownButton() {}

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Down Button";
        return os;
    }
    std::string label() const override {
        return "Down";
    }    
};

static const IButton* UP_BUTTON = new UpButton();
static const IButton* DOWN_BUTTON = new DownButton();

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

static const IButtonState* PRESSED_STATE = new PressedState();
static const IButtonState* RELEASED_STATE = new ReleasedState();

class ElevatorPanel : public IPanel {
    private:
    IButton* downButton;
    IButtonState* downButtonState;
    IButton* upButton;
    IButtonState* upButtonState;

    public:
    ElevatorPanel() 
        : downButton((IButton*)DOWN_BUTTON), downButtonState((IButtonState*)RELEASED_STATE),
          upButton((IButton*)UP_BUTTON), upButtonState((IButtonState*)RELEASED_STATE) {}

    ~ElevatorPanel() {}

    ElevatorPanel(const ElevatorPanel& other) 
        : downButton(other.downButton), downButtonState(other.downButtonState),
          upButton(other.upButton), upButtonState(other.upButtonState) {}

    ElevatorPanel& operator=(const ElevatorPanel& other) {
        if (this != &other) {
            downButton = other.downButton;
            downButtonState = other.downButtonState;
            upButton = other.upButton;
            upButtonState = other.upButtonState;
        }
        return *this;
    }

    ElevatorPanel(ElevatorPanel&& other) noexcept
        : downButton(other.downButton), downButtonState(other.downButtonState),
          upButton(other.upButton), upButtonState(other.upButtonState) {
        // other.downButton = nullptr;
        // other.downButtonState = nullptr;
        // other.upButton = nullptr;
        // other.upButtonState = nullptr;
    }

    ElevatorPanel& operator=(ElevatorPanel&& other) noexcept {
        if (this != &other) {
            downButton = other.downButton;
            downButtonState = other.downButtonState;
            upButton = other.upButton;
            upButtonState = other.upButtonState;

            // other.downButton = nullptr;
            // other.downButtonState = nullptr;
            // other.upButton = nullptr;
            // other.upButtonState = nullptr;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os) const override {
        os << "Panel Status:\n";
        os << "  " << upButton << ": " << upButtonState << "\n";
        os << "  " << downButton << ": " << downButtonState << "\n";
        return os;
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