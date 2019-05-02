/**
  * @file
  */

#include "controller.hpp"
#include "game.hpp"
#include "entity.hpp"


namespace Engy
{

Controller::Controller(Entity * e)
    : game_  ([e]() { assert(e); return e->game(); } ())
    , entity_(e)
{
    assert(game_);

    game_->scene()->addItem(this);
    deleteControllerIfEntityDeleted(true);
    deleteControllerIfGameDeleted(true);
}


Game * Controller::game()
{
    return game_;
}


Entity * Controller::entity()
{
    return entity_;
}


void Controller::paint(QPainter * painter,
                       QStyleOptionGraphicsItem const * option, QWidget * widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


QRectF Controller::boundingRect() const
{
    return { 0, 0, 0, 0 };
}


void Controller::harakiri()
{
    delete this;
}


void Controller::deleteControllerIfEntityDeleted(bool val)
{
    if (val == true && deleteControllerIfEntityDeleted_ == false) {
        deleteControllerIfEntityDeleted_ = true;
        connect(entity_, &Entity::destroyed, this, &Controller::harakiri);
    }
    if (val == false && deleteControllerIfEntityDeleted_ == true) {
        deleteControllerIfEntityDeleted_ = false;
        disconnect(entity_, &Entity::destroyed, this, &Controller::harakiri);
    }
}


void Controller::deleteControllerIfGameDeleted(bool val)
{
    if (val == true && deleteControllerIfGameDeleted_ == false) {
        deleteControllerIfGameDeleted_ = true;
        connect(game_, &Game::destroyed, this, &Controller::harakiri);
    }
    if (val == false && deleteControllerIfGameDeleted_ == true) {
        deleteControllerIfGameDeleted_ = false;
        disconnect(game_, &Game::destroyed, this, &Controller::harakiri);
    }
}

} // Engy







