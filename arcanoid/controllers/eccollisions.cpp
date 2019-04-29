#include "eccollisions.hpp"


ECCollisions::ECCollisions(QGraphicsScene * scene, EntityW entity,
                           const FieldP field, Timer const * timer)
    : Controller(scene, entity)
    , field_(field)
    , timer_(timer)
{
    assert(scene);
    assert(timer);

    // WARNING: It should be return after emitting "entityDeleted"
    connect(this, &ECCollisions::entityDeleted, this, &ECCollisions::harakiri);
    connect(timer, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


ECCollisions::~ECCollisions()
{
    disconnect(timer_, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


void ECCollisions::checkCollisions()
{
    auto e = entity().lock();
    if (!e) {
        emit entityDeleted();
        return;
    }

    for (auto item : field_->entities()) {
        auto i = item.lock();
        if (!i) {
            continue;
        }

        if (e->form() != i->form() && e->form()->collidesWithItem(i->form())) {
            processCollision(i);
        }
    }
}


void ECCollisions::processCollision(EntityS e)
{
    // TODO
}








