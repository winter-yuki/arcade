#include "collisions.hpp"

#include "entity.hpp"


namespace Engy
{

Collisions::Collisions(int checkingInterval)
{
    connect(this, &Collisions::entitySetted, [this, checkingInterval] {
        startTimer(checkingInterval);
    });
}


void Collisions::addHandler(Component::Id handler)
{
    hs_.push_back(handler);
}


void Collisions::addHandler(Component * handler)
{
    addHandler(handler->id());
}


void Collisions::rmHandler(Component::Id id)
{
    hs_.erase(remove(hs_.begin(), hs_.end(), id), hs_.end());
}


void Collisions::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)

    assert(entity());
    assert(entity()->game());
    for (Entity * other : entity()->game()->entities()) {
        assert(other);
        assert(other->form());
        if (entity()->form() != other->form() &&
                entity()->form()->collidesWithItem(other->form())) {
            applyHandlers(entity(), other);
        }
    }
}


void Collisions::applyHandlers(Entity * a, Entity * b)
{
    assert(a && b);

    for (auto h : hs_) {
        auto component = entity()->findComponent(h);
        if (!component) {
            continue;
        }

        if (auto handler = dynamic_cast<CollisionHandler *>(component)) {
            handler->handler()(a, b);
        } else {
            assert("Collision handler should be derived "
                   "from class CollisionHandler" && false);
        }
    }
}


CollisionHandler::CollisionHandler(Component::Id id)
    : Component(id)
{}

} // Engy
























