#include "entity.hpp"


namespace Engy
{

Entity::Entity(QGraphicsScene * scene)
    : scene_(scene)
{
    assert(scene);
}


void Entity::addForm(QGraphicsItem * form)
{
    assert(form);
    form_ = form;
    scene_->addItem(form_);
}


QGraphicsItem * Entity::form()
{
    return form_;
}


void Entity::addComponent(ComponentU component)
{
    component->setEntity(this);
    components_.insert({component->id(), std::move(component)});
}


void Entity::removeComponent(Component::Id id)
{
    components_.erase(id);
}


std::optional<Component *> Entity::findComponent(Component::Id id)
{
    auto it = components_.find(id);
    if (it != components_.end()) {
        return { it->second.get() };
    }
    return std::nullopt;
}

}





