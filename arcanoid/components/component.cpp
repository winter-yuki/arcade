#include "component.hpp"


void Component::setEntity(Entity * e)
{
    entity_ = e;
}


Entity * Component::entity()
{
    return entity_;
}
