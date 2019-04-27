#include "timer.hpp"


Timer::Timer(QObject * parent)
    : QTimer(parent)
{
    connect(this, &Timer::timeout, this, &Timer::timeUpdate);
}


void Timer::timeUpdate()
{
    prevTime_ += interval();
    emit tick(prevTime_);
}
