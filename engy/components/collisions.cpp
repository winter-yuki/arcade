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
    if (entity()) {
        entity()->addComponent(handler);
    }
    addHandler(handler->id());
}


void Collisions::addHandlers(std::initializer_list<Component::Id> l)
{
    hs_.insert(hs_.end(), l.begin(), l.end());
}


void Collisions::addHandlers(std::initializer_list<Component *> l)
{
    transform(l.begin(), l.end(), std::back_inserter(hs_),
              [this](Component * c) {
        if (entity()) {
            entity()->addComponent(c);
        }
        return c->id();
    });
}


void Collisions::setMarkerTime(int interval)
{
    assert(interval >= 0);
    collisionMarker_ = interval;
}


int Collisions::markerTimer() const
{
    return collisionMarker_;
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
        if (!other->form()) {
            continue;
        }

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

    addMarker<RecentlyCollided>(a, collisionMarker_);
}


CollisionHandler::CollisionHandler(Component::Id id)
    : Component(id)
{}

} // Engy
























