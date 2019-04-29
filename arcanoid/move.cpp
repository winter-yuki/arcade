#include "move.hpp"

#include "entity.hpp"


Move::Move(Timer const * timer)
    : timer_(timer)
{
    connect(timer, &Timer::tick, this, &Move::update);
}


Move::~Move()
{
    disconnect(timer_, &Timer::tick, this, &Move::update);
}


void Move::setV(QVector2D v)
{
    v_ = v;
}


QVector2D Move::v() const
{
    return v_;
}


void Move::update(int64_t dt)
{
    dt /= 1000; // to seconds
    entity()->form()->moveBy(double(v_.x()) * dt, double(v_.y()) * dt);
}














