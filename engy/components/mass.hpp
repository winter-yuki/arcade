#pragma once

#include "component.hpp"


namespace Engy
{

class Mass final
        : public Component {
public:
    explicit Mass(double m);

    void setM(double m);
    double m() const;

private:
    double m_;
};

} // Engy
