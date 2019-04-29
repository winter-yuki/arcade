#pragma once

#include "controller.hpp"
#include "timer.hpp"
#include "field.hpp"


class ECCollisions final
        : public Controller {
    Q_OBJECT

public:
    // 1st: given entity, 2nd: other entity from field.
    // Shared poiners are guaranted not to be empty.
    using Handler = std::function<void (EntityS &, EntityS &)>;

    ECCollisions(QGraphicsScene * scene, EntityW entity,
                 const FieldP field, Timer const * timer);
    ~ECCollisions();

    void setHandler(Handler h);

public slots:
    void checkCollisions();

private:
    FieldP field_;
    Timer const * timer_;
    Handler h_ = [](EntityS & /*a*/, EntityS & /*b*/) {};
};
