#pragma once

#include "value.hpp"


namespace Engy
{

class Mass final
        : public Value<double> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit Mass(double m = 0);
};

} // Engy
