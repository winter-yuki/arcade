#include "mass.hpp"


namespace Engy
{

Mass::Mass(double m)
    : m_(m)
{}


void Mass::setM(double m)
{
    m_ = m;
}


double Mass::m() const
{
    return m_;
}

} // Engy
