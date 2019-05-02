/**
  * @file
  */

#include "ecscenebounds.hpp"

#include "stdafx.hpp"
#include "game.hpp"


namespace Engy
{

ECSceneBounds::ECSceneBounds(Entity * entity)
    : Controller(entity)
    , timer_(game()->timer())
{
    assert(timer_);

    connect(timer_, &Timer::timeout, this, &ECSceneBounds::check);
}


void ECSceneBounds::check()
{
    const auto pos = [this]() -> QPointF {
        const auto rect = entity()->form()->boundingRect();
        const auto epos = entity()->form()->pos();
        return epos + QPointF(rect.width(), rect.height()) / 2;
    } ();

    if (!(pos.x() >= 0 && pos.x() <= game()->sceneSize().width() &&
          pos.y() >= 0 && pos.y() <= game()->sceneSize().height())) {
        emit isOut();
    }
}

} // Engy















