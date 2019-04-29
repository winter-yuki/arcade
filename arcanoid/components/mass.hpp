#pragma once

#include "component.hpp"


class Mass final
        : public Component {
public:
    explicit Mass(double m);

    void setM(double m);
    double m() const;

    Id id() const override { return Component::id<Mass>(); }

private:
    double m_;
};
