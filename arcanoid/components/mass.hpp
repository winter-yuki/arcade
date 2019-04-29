#pragma once

#include "component.hpp"


class Mass final
        : public Component {
public:
    explicit Mass(double m);

    void setM(double m);
    double m() const;

private:
    double m_;
};
