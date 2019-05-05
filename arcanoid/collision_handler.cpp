#include "collision_handler.hpp"

#include "mainwindow.hpp"
#include "components.hpp"
#include "engy/controllers/collision_handlers.hpp"


void collisionHandler(MainWindow * main, Engy::Entity * a, Engy::Entity * b)
{
    assert(main && a && b);

    Engy::basicCollisionHandler(a, b);

    if (a->name() == "Ball" && b->name() == "Player") {
        main->updateScore(10);
    }

    if (a->name() == "Ball" && b->name() == "Box") {
        if (auto hp = b->findComponent<HP>()) {
            hp->changeHp();
            if (hp->hp() <= 0) {
                b->deleteLater();
                return;
            }
        }
    }
}
