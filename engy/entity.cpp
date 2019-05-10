/**
  * @file
  */

#include "entity.hpp"

#include "game.hpp"


namespace Engy
{

Entity::Entity(Game * game)
    : game_(game)
    , fh_(new FocusHandler)
{
    assert(game);
    assert(game->scene());

    game_->scene()->addItem(fh_);
    connect(fh_, &FocusHandler::keyPressed, this, &Entity::keyPressed);
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
        deleteComponent(it->second);
    }

    qDebug() << "Entity deleted";
}


void Entity::setName(QString name)
{
    name_ = std::move(name);
}


QString Entity::name() const
{
    return name_;
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
    bool deleted = delForm();
    form_ = form;
    game_->scene()->addItem(form_);
    if (!deleted) {
        emit formAdded();
    }
    emit formChanged();
}


bool Entity::delForm()
{
    if (game_ && form_ && form_->scene()) {
        game_->scene()->removeItem(form_);
        form_ = nullptr;
        return true;
    }
    return false;
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


QGraphicsItem * Entity::extractForm()
{
    auto form = form_;
    delForm();
    return form;
}


void Entity::setFocus()
{
    fh_->setFocus();
}


bool Entity::hasFocus() const
{
    return fh_->hasFocus();
}


void Entity::gameDeleted()
{
    game_ = nullptr;
    form_ = nullptr;
    delete this;
}


void Entity::addComponent(Component * component)
{
    auto search = components_.find(component->id());
    if (search != components_.end()) {
        deleteComponent(search->second);
        search->second = component;
    } else {
        components_.insert({component->id(), component});
    }
    component->setEntity(this);
}


bool Entity::removeComponent(Component::Id id)
{
    auto search = components_.find(id);
    if (search != components_.end()) {
        deleteComponent(search->second);
        components_.erase(search);
        return true;
    }
    return false;
}


Component * Entity::findComponent(Component::Id id)
{
    auto it = components_.find(id);
    if (it != components_.end()) {
        return it->second;
    }
    return nullptr;
}


void Entity::forgetComponent(Component::Id id)
{
    auto rez = components_.erase(id);
    assert("Component should be added to entity" && rez);
}


void Entity::deleteComponent(Component * c) const
{
    c->delEntity();
    delete c;
}


Entity::FocusHandler::FocusHandler()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
}


void Entity::FocusHandler::keyPressEvent(QKeyEvent * event)
{
    emit keyPressed(event);
}


void Entity::FocusHandler::paint(QPainter * painter,
                                 QStyleOptionGraphicsItem const * option,
                                 QWidget * widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


QRectF Entity::FocusHandler::boundingRect() const
{
    return { 0, 0, 0, 0 };
}

} // Engy





