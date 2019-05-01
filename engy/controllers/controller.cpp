/**
  * @file
  */

#include "controller.hpp"
#include "game.hpp"


namespace Engy
{

Controller::Controller(Game * game, EntityW e)
    : game_  (game)
    , entity_(e)
{
    assert(game);
    assert(!e.expired());

    game->scene()->addItem(this);
    deleteControllerIfEntityDeleted(true);
    deleteControllerIfGameDeleted(true);
}


Controller::~Controller()
{
    /// Disconnect everything from this object
    /// @warning cppcheck red warning: null pointer dereference.
    /// @todo remove
    disconnect(nullptr, nullptr, this, nullptr);
}


Game * Controller::game()
{
    return game_;
}


EntityS Controller::entity()
{
    auto l = entity_.lock();
    if (!l) {
        emit entityDeleted();
    }
    return l;
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
        connect(this, &Controller::entityDeleted, this, &Controller::harakiri);
    }
    if (val == false && deleteControllerIfEntityDeleted_ == true) {
        deleteControllerIfEntityDeleted_ = false;
        disconnect(this, &Controller::entityDeleted, this, &Controller::harakiri);
    }
}


void Controller::deleteControllerIfGameDeleted(bool val)
{
    if (val == true && deleteControllerIfGameDeleted_ == false) {
        deleteControllerIfGameDeleted_ = true;
        connect(game_, &Game::deleted, this, &Controller::harakiri);
    }
    if (val == false && deleteControllerIfGameDeleted_ == true) {
        deleteControllerIfGameDeleted_ = false;
        disconnect(game_, &Game::deleted, this, &Controller::harakiri);
    }
}

} // Engy







