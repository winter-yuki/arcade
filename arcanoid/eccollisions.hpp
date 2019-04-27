#pragma once

#include "controller.hpp"
#include "timer.hpp"
#include "field.hpp"


class ECCollisions final
        : public  Controller {
    Q_OBJECT

public:
    ECCollisions(QGraphicsScene * scene, EntityP entity,
                 const FieldP field, Timer const * timer);
    ~ECCollisions();

public slots:
    void checkCollisions();

private:
    void processCollision(EntityP e);

private:
    FieldP field_;
    Timer const * timer_;
};
