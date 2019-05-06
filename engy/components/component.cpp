/**
  * @file
  */

#include "component.hpp"

#include "entity.hpp"


namespace Engy
{

Component::Component(Id id)
    : id_(id)
{}


Component::~Component()
{
    if (entity_) {
        entity_->forgetComponent(id_);
    }
}


Component::Id Component::id() const
{
    return id_;
}


Entity * Component::entity()
{
    return entity_;
}


void Component::setEntity(Entity * e)
{
    assert("Component shound have only one parent" && !entity_);
    entity_ = e;
    emit entitySetted();
}


void Component::delEntity()
{
    entity_ = nullptr;
    emit entityDeleted();
}

} // Engy
