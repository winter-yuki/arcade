#include <QProgressBar>

#include "mainwindow.hpp"

#include "entities.hpp"
#include "engy/game.hpp"
#include "engy/controllers/ecarrowkeys.hpp"
#include "engy/components/move.hpp"
#include "engy/controllers/eccollisions.hpp"
#include "engy/controllers/collision_handlers.hpp"
#include "engy/controllers/ecscenebounds.hpp"
#include "engy/components/mass.hpp"


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    auto game = new Engy::Game(&window);
    game->setSceneSize({1000, 900});
    game->setBg(QPixmap(":/images/hydra.jpg").scaled(game->sceneSize()));
    window.setFixedSize(game->size());

    // Create player
    double borderWidth = 5;
    auto player = Engy::Entity::create<Player>(game);
    auto keyController = Engy::Controller::create<Engy::ECArrowKeys>(player);
    keyController->setDx(25);
    keyController->setDy(std::nullopt);
    keyController->setLBorder(borderWidth);
    keyController->setRBorder(borderWidth);

    // Add bounds
    auto borders = makeBorders(game, borderWidth);

    // Create ball
    auto ball = Engy::Entity::create<Ball>(game);

    auto move = Engy::Component::create<Engy::Move>();
    move->setV({.3f, 0.4f});
    ball->addComponent(move);
    // delete move; // Component can be deleted outside.

    auto collisions = Engy::Controller::create<Engy::ECCollisions>(ball);
    collisions->setHandler(Engy::basicCollisionHandler);

    auto outOfScene = Engy::Controller::create<Engy::ECSceneBounds>(ball);
    QObject::connect(outOfScene, &Engy::ECSceneBounds::isOut, [outOfScene] {
        delete outOfScene->entity();
    });

    game->launch();
    window.show();
    return QApplication::exec();
}







