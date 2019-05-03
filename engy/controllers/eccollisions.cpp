/**
  * @file
  */

#include "eccollisions.hpp"

#include "game.hpp"
#include "entity.hpp"


namespace Engy
{

ECCollisions::ECCollisions(Entity * entity)
    : Controller(entity)
    , timer_(game()->timer())
{
    assert(entity->form());
    connect(timer_, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


void ECCollisions::setHandler(Handler h)
{
    h_ = std::move(h);
}


void ECCollisions::checkCollisions()
{
    for (Entity * other : game()->entities()) {
        assert(other);
        assert(other->form());
        if (entity()->form() != other->form() &&
                entity()->form()->collidesWithItem(other->form())) {
            assert(h_);
            h_(entity(), other);
        }
    }
}

} // Engy




