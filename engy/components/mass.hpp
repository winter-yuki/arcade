/**
  * @file
  */

#pragma once

#include "component.hpp"


namespace Engy
{

/**
 * @ingroup component
 * @brief The Mass class
 */
class Mass final
        : public Component {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit Mass(double m);

public:
    void setM(double m);
    double m() const;

private:
    double m_;
};

} // Engy
