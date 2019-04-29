#include "component.hpp"


Component::Id Component::getId() const
{
    return { typeid (this) };
}


void Component::setEntity(Entity * e)
{
    entity_ = e;
}


Entity * Component::entity()
{
    return entity_;
}
