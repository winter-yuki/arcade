#include "component.hpp"


Component::Component(Entity * owner)
    : entity_(owner)
{}


Component::Id Component::getId() const
{
    return { typeid (this) };
}


Entity * Component::entity()
{
    return entity_;
}
