#pragma once

#include "engy/components/value.hpp"


class HP final
        : public Engy::Value<HP, int> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit HP(int hp = 100)
      : Engy::Value<HP, int>(hp)
    {}
};
