/**
  * @file
  */

#pragma once

#include "controller.hpp"
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
    ENGY_CREATABLE_CONTROLLER

    engy_controller_ctor:
        explicit ECSceneBounds(Entity * entity);

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
    Timer * timer_ = nullptr; ///< To avoid cppcheck warning.
};

} // Engy

