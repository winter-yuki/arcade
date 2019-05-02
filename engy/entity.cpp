/**
  * @file
  */

#include "entity.hpp"

#include "game.hpp"


namespace Engy
{

EntityS Entity::create(Game * game) {
    assert(game);
    /// @todo Create via std::make_shared
    /// (it should be marked "friend" for the Entity)
    std::shared_ptr<Entity> entity(new Entity(game));
    game->addEntity(entity);
    return entity;
}


Entity::Entity(Game * game)
    : game_(game)
{
    assert(game);
}


Entity::~Entity()
{
    if (form_) {
        game_->scene()->removeItem(form_);
    }

    // Make all components forget about parent to avoid cycle.
    for (auto it = components_.begin(); it != components_.end(); ++it) {
        assert(it->second->entity());
        it->second->delEntity();
    }
}


void Entity::addForm(QGraphicsItem * form)
{
    if (form_) {
        game_->scene()->removeItem(form_);
    }
    form_ = form;
    game_->scene()->addItem(form_);
}


QGraphicsItem * Entity::form()
{
    return form_;
}


void Entity::addComponent(Component * component)
{
    component->setEntity(this);
    components_.insert({component->id(), ComponentU(component)});
}


bool Entity::removeComponent(Component::Id id)
{
    return components_.erase(id);
}


std::optional<Component *> Entity::findComponent(Component::Id id)
{
    auto it = components_.find(id);
    if (it != components_.end()) {
        return { it->second.get() };
    }
    return std::nullopt;
}


void Entity::forgetComponent(Component::Id id)
{
    auto node = components_.extract(id);
    assert("Entity should be parent if component knows about it" &&
           !node.empty());
    node.mapped().release();
}

} // Engy





