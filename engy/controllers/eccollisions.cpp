/**
  * @file
  */

#include "eccollisions.hpp"

#include "game.hpp"
#include "entity.hpp"


namespace Engy
{

ECCollisions::ECCollisions(EntityW entity)
    : Controller(entity)
    , timer_(game()->timer())
    , field_(game()->field())
{
    assert(ifHasForm(entity));

    connect(timer_, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


void ECCollisions::setHandler(Handler h)
{
    h_ = std::move(h);
}


void ECCollisions::checkCollisions()
{
    auto e = entity();
    if (!e) {
        return;
    }

    for (auto item : field_->entities()) {
        auto i = item.lock();
        if (!i) {
            continue;
        }

        assert(e->form() && i->form());
        if (e->form() != i->form() && e->form()->collidesWithItem(i->form())) {
            assert(h_);
            h_(e, i);
        }
    }
}

} // Engy




