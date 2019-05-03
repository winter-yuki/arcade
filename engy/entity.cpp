/**
  * @file
  */

#include "entity.hpp"

#include "game.hpp"


namespace Engy
{

Entity * Entity::create(Game * game) {
    assert(game);
    auto entity = new Entity(game);
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
    delForm();
    if (game_) {
        auto rez = game()->forgetEntity(this);
        assert(rez);
    }

    // Make all components forget about parent to avoid cycle.
    for (auto it = components_.begin(); it != components_.end(); ++it) {
        assert(it->second->entity());
        it->second->delEntity();
    }

    qDebug() << "Entity deleted";
}


Game * Entity::game()
{
    return game_;
}


Game const * Entity::game() const
{
    return game_;
}


void Entity::addForm(QGraphicsItem * form)
{
    assert(game_);
    if (form_ && form_->scene()) {
        game_->scene()->removeItem(form_);
    }
    form_ = form;
    game_->scene()->addItem(form_);
}


void Entity::delForm()
{
    if (game_ && form_ && form_->scene()) {
        game_->scene()->removeItem(form_);
        form_ = nullptr;
    }
}


void Entity::delGame()
{
    game_ = nullptr;
    form_ = nullptr;
}


QGraphicsItem * Entity::form()
{
    return form_;
}


QGraphicsItem const * Entity::form() const
{
    return form_;
}


void Entity::gameDeleted()
{
    game_ = nullptr;
    form_ = nullptr;
    delete this;
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
    node.mapped()->delEntity();
    node.mapped().release();
}

} // Engy





