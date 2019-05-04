#include "engy/game.hpp"
#include "engy/controllers/ecarrowkeys.hpp"
#include "engy/components/move.hpp"
#include "engy/controllers/eccollisions.hpp"
#include "engy/controllers/collision_handlers.hpp"
#include "engy/controllers/ecscenebounds.hpp"
#include "engy/components/mass.hpp"


Engy::Entity * makeBall(Engy::Game & game);
std::vector<Engy::Entity *> makeBorders(Engy::Game & game, double width = 10);


class Player final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        Player(Engy::Game * game)
    : Engy::Entity(game) {
        const auto gsw = game->sceneSize().width();
        const auto gsh = game->sceneSize().height();
        auto * platform = new QGraphicsRectItem(QRectF{0, 0, 200, 10});
        platform->setPos({gsw / 2 - platform->boundingRect().width() / 2,
                          gsh - platform->boundingRect().height()});
        QColor color(0xAA00BB);
        platform->setPen({color});
        platform->setBrush({color});

        addForm(platform);
        setName("Player");
    }
};


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    Engy::Game game;

    game.setSceneSize({1000, 900});
    game.setBg(QPixmap(":/images/hydra.jpg").scaled(game.sceneSize()));

    // Create player
    double borderWidth = 5;
    auto player = Engy::Entity::create<Player>(&game);
    auto keyController = Engy::Controller::create<Engy::ECArrowKeys>(player);
    keyController->setDx(25);
    keyController->setDy(std::nullopt);
    keyController->setLBorder(borderWidth);
    keyController->setRBorder(borderWidth);

    // Add bounds
    auto borders = makeBorders(game, borderWidth);

    // Create ball
    auto ball = makeBall(game);

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

    game.launch();

    return QApplication::exec();
}


Engy::Entity * makeBall(Engy::Game & game)
{
    QColor ballColor(QRgb(0x00AADD));

    auto * ball = new QGraphicsEllipseItem;
    ball->setRect({0, 0, 30, 30});
    ball->moveBy(100, 100);
    ball->setBrush(QBrush(ballColor));
    ball->setPen(QPen(ballColor));

    auto entity = Engy::Entity::create(&game);
    entity->addForm(ball);
    return entity;
}


std::vector<Engy::Entity *> makeBorders(Engy::Game & game, double width)
{
    const qreal gsh = game.sceneSize().height();
    const qreal gsw = game.sceneSize().width();

    QColor borderColor(QRgb(0x00AA00));
    std::array rects = {
        new QGraphicsRectItem(QRectF{0, 0, width, gsh}),
        new QGraphicsRectItem(QRectF{0, 0, gsw, width}),
        new QGraphicsRectItem(QRectF{gsw - width, 0, width, gsh})
    };

    for (auto rect : rects) {
        rect->setBrush(QBrush(borderColor));
        rect->setPen(QPen(borderColor));
    }

    std::vector<Engy::Entity *> borders(rects.size());
    for (size_t i = 0; i < borders.size(); ++i) {
        borders[i] = Engy::Entity::create(&game);
        borders[i]->addForm(rects[i]);
    }
    return borders;
}






