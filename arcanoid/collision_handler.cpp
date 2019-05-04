#include "collision_handler.hpp"

#include "mainwindow.hpp"
#include "engy/controllers/collision_handlers.hpp"


void collisionHandler(MainWindow * main, Engy::Entity * a, Engy::Entity * b)
{
    if (a->name() == "Ball" && b->name() == "Player") {
        main->updateScore(10);
    }
    Engy::basicCollisionHandler(a, b);
}
