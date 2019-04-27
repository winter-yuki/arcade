#include "eccollisions.hpp"


ECCollisions::ECCollisions(QGraphicsScene * scene, EntityP entity,
                           const FieldP field, Timer const * timer)
    : Controller(scene, entity)
    , field_(field)
    , timer_(timer)
{
    assert(scene);
    assert(timer);

    connect(timer, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


ECCollisions::~ECCollisions()
{
    disconnect(timer_, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


void ECCollisions::checkCollisions()
{
    for (auto item : field_->entities()) {
        if (entity()->form() != item->form() &&
                entity()->form()->collidesWithItem(item->form())) {
            processCollision(item);
        }
    }
}


void ECCollisions::processCollision(EntityP e)
{
    // TODO
}








