#include "move.hpp"

#include "entity.hpp"


namespace Engy
{

Move::Move(int64_t fps)
    : Component(id<Move>())
    , interval_([fps]() { assert(fps > 0); return int64_t(1.0 / fps * 1000); } ())
{
    connect(this, &Move::entitySetted, [this]() {
        startTimer(int(interval_));
    });
}


void Move::setV(QVector2D v)
{
    v_ = v;
}


QVector2D Move::v() const
{
    return v_;
}


void Move::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event)
    update(interval_);
}


void Move::update(int64_t dt)
{
    entity()->form()->moveBy(double(v_.x()) * dt, double(v_.y()) * dt);
}

} // Engy












