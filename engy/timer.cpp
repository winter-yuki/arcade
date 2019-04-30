#include "timer.hpp"


namespace Engy
{

Timer::Timer(QObject * parent)
    : QTimer(parent)
{
    connect(this, &Timer::timeout, this, &Timer::timeUpdate);
}


int64_t Timer::time() const
{
    return time_;
}


void Timer::timeUpdate()
{
    time_ += interval();
    emit tickdt(interval());
    emit tickTime(time_);
}

} // Engy
