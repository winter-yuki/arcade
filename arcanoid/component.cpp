#include "component.hpp"


Component::Id Component::getId() const
{
    return { typeid (*this) };
}
