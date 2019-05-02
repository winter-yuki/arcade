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
    ENGY_CREARABLE_COMPONENT

public:
    void setM(double m);
    double m() const;

private:
    explicit Mass(double m);

private:
    double m_;
};

} // Engy
