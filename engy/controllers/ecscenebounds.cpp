#include "ecscenebounds.hpp"

#include "stdafx.hpp"
#include "game.hpp"


namespace Engy
{

ECSceneBounds::ECSceneBounds(Game * game, EntityW entity)
    : Controller(game, entity)
    , timer_([game]() { assert(game); return game->timer(); } ())
{
    assert(!entity.expired());
    assert(ifHasForm(entity));

    /// @warning Place "return" after emitting "entityDeleted"
    connect(this, &ECSceneBounds::entityDeleted, this, &ECSceneBounds::harakiri);
    connect(timer_, &Timer::timeout, this, &ECSceneBounds::check);
}


ECSceneBounds::~ECSceneBounds()
{
    disconnect(timer_, &Timer::timeout, this, &ECSceneBounds::check);
}


void ECSceneBounds::check()
{
    auto e = entity().lock();
    if (!e) {
        emit entityDeleted();
        return;
    }

    const auto pos = [&e]() -> QPointF {
        const auto rect = e->form()->boundingRect();
        const auto epos = e->form()->pos();
        return epos + QPointF(rect.width(), rect.height()) / 2;
    } ();

    if (!(pos.x() >= 0 && pos.x() <= game()->sceneSize().width() &&
          pos.y() >= 0 && pos.y() <= game()->sceneSize().height())) {
        emit isOut();
    }
}

} // Engy















