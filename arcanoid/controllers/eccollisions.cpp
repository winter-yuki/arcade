#include "eccollisions.hpp"


ECCollisions::ECCollisions(QGraphicsScene * scene, EntityW entity,
                           const FieldP field, Timer const * timer)
    : Controller(scene, entity)
    , field_(field)
    , timer_(timer)
{
    assert(!entity.expired());
    // If entity has form
    assert([&entity]() -> bool { auto l = entity.lock(); return l->form(); }());
    assert(scene);
    assert(field);
    assert(timer);

    // WARNING: It should be return after emitting "entityDeleted"
    connect(this, &ECCollisions::entityDeleted, this, &ECCollisions::harakiri);
    connect(timer, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


ECCollisions::~ECCollisions()
{
    disconnect(timer_, &Timer::timeout, this, &ECCollisions::checkCollisions);
}


void ECCollisions::setHandler(Handler h)
{
    h_ = std::move(h);
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

        assert(e->form() && i->form());
        if (e->form() != i->form() && e->form()->collidesWithItem(i->form())) {
            assert(h_);
            h_(e, i);
        }
    }
}






