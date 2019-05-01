#include "entity.hpp"
#include "game.hpp"


namespace Engy
{

EntityS Entity::create(Game * game) {
    assert(game);
    /// @todo Do this via std::make_shared
    /// (it should be marked "friend" for the Entity)
    std::shared_ptr<Entity> entity(new Entity(game));
    game->addEntity(entity);
    return entity;
}


Entity::Entity(Game * game)
    : scene_([game]() { assert(game); return game->scene(); } ())
{}


Entity::~Entity()
{
    scene_->removeItem(form_);
    for (auto it = components_.begin(); it != components_.end(); ++it) {
        assert(it->second->entity());
        it->second->delEntity();
    }
}


void Entity::addForm(QGraphicsItem * form)
{
    assert(form);
    assert(scene_);
    form_ = form;
    scene_->addItem(form_);
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
    assert(!node.empty());
    node.mapped().release();
}

} // Engy





