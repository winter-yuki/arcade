#include "entities.hpp"

#include "components.hpp"


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












