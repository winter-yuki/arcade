/**
  * @file
  */

#pragma once

#include "controller.hpp"
#include "entityptrs.hpp"
#include "timer.hpp"


namespace Engy
{

class Game;

/**
 * @brief Checks if center of object's bounting rect is out of scene.
 */
class ECSceneBounds final
        : public Controller {
    Q_OBJECT

public:
    ECSceneBounds(Game * game, EntityW entity);

public slots:
    /**
     * @brief Checks if center of object's bounting rect is out of scene.
     */
    void check();

signals:
    /**
     * @brief Emitted when object is out of scene.
     */
    void isOut();

private:
    Timer * timer_;
};

} // Engy

