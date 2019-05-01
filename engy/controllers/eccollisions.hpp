/**
  * @file
  */

#pragma once

#include "controller.hpp"
#include "timer.hpp"
#include "field.hpp"


namespace Engy
{

/**
 * @brief The ECCollisions class
 */
class ECCollisions final
        : public Controller {
    Q_OBJECT

public:
    /**
     * 1st: given entity, 2nd: other entity from field.
     * Shared poiners are guaranted not to be empty.
     */
    using Handler = std::function<void (EntityS &, EntityS &)>;

    ECCollisions(Game * game, EntityW entity);

    void setHandler(Handler h);

public slots:
    void checkCollisions();

private:
    Timer * timer_;
    FieldS field_;
    Handler h_ = [](EntityS & /*a*/, EntityS & /*b*/) {};
};

} // Engy
