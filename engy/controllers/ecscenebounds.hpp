#pragma once

#include "controller.hpp"
#include "entityptrs.hpp"
#include "timer.hpp"


namespace Engy
{

class Game;

class ECSceneBounds final
        : public Controller {
    Q_OBJECT

public:
    ECSceneBounds(Game * game, EntityW entity);
    ~ECSceneBounds() override;

public slots:
    void check();

signals:
    void isOut();

private:
    Timer * timer_;
};

} // Engy

