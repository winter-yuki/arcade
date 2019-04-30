#include "component.hpp"


namespace Engy
{

Entity * Component::entity()
{
    return entity_;
}


void Component::setEntity(Entity * e)
{
    entity_ = e;
    emit entitySetted();
}

} // Engy
