#pragma once

#include "component.hpp"


namespace Engy
{

class Intangible final
        : public ComponentT<Intangible> {
    ENGY_CREATABLE_COMPONENT
    engy_component_ctor:
        Intangible() = default;
};

} // Engy
