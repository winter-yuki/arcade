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
}


Game * Controller::game()
{
    return game_;
}


EntityW Controller::entity()
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

} // Engy







