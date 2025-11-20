#ifndef PANEL_H
#define PANEL_H

#include <iostream>
#include <map>

class IButtonState {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

class IButton {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

class IPanel {
    public:
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

#endif // PANEL_H