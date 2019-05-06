#include "entities.hpp"

#include "components.hpp"
#include "engy/components/intangible.hpp"
#include "engy/components/move.hpp"
#include "engy/controllers/ecscenebounds.hpp"
#include "engy/controllers/eccollisions.hpp"


Player::Player(Engy::Game * game)
    : Engy::Entity(game)
{
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


Ball::Ball(Engy::Game * game)
    : Engy::Entity(game)
{
    QColor ballColor(QRgb(0x00AADD));

    auto * ball = new QGraphicsEllipseItem;
    ball->setRect({0, 0, 30, 30});

    ball->setBrush(QBrush(ballColor));
    ball->setPen(QPen(ballColor));

    addForm(ball);
    setName("Ball");
}


Box::Box(Engy::Game * game, QRectF rect)
    : Engy::Entity(game)
{
    auto form = new QGraphicsRectItem(rect);

    QColor color(0xAA00DD);
    form->setPen(QPen(color));
    form->setBrush(QBrush(color));

    addForm(form);
    setName("Box");
}


Bonus::Bonus(Engy::Game * game, Engy::Entity * ancestor,
             Engy::ECCollisions::Handler applier)
    : Engy::Entity(game)
{
    assert(ancestor);
    assert(applier);

    setName("Bonus");

    auto awidth  = ancestor->form()->boundingRect().width();
    auto aheight = ancestor->form()->boundingRect().height();
    auto rect = new QGraphicsRectItem(QRectF{0, 0, awidth / 2, aheight / 2});
    addForm(rect);
    form()->setPos(ancestor->form()->pos() + QPointF{awidth / 2, aheight / 2});

    auto move = Engy::Component::create<Engy::Move>();
    move->setV({0, 0.2f});
    addComponent(move);
    addComponent(Engy::Component::create<Engy::Intangible>());

    auto bounds = Engy::Controller::create<Engy::ECSceneBounds>(this);
    connect(bounds, &Engy::ECSceneBounds::isOut, [this] {
        deleteLater();
    });

    auto collisions = Engy::Controller::create<Engy::ECCollisions>(this);
    collisions->setHandler([&applier](Engy::Entity * a, Engy::Entity * b) {
        assert(a->name() == "Bonus");
        if (b->name() == "Player") {
            assert(applier);
            applier(a, b);
            a->deleteLater();
        }
    });
}










