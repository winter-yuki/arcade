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

    auto hp = Engy::Component::create<HP>();
    addComponent(hp);

    addForm(form);
    setName("Box");
}


std::vector<Engy::Entity *> makeBorders(Engy::Game * game, double width)
{
    const qreal gsh = game->sceneSize().height();
    const qreal gsw = game->sceneSize().width();

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
        borders[i] = Engy::Entity::create(game);
        borders[i]->addForm(rects[i]);
        borders[i]->setName(QString("Border %1").arg(i));
    }
    return borders;
}


std::vector<Engy::Entity *> makeField(Engy::Game * game)
{
    // TODO components

    const int upOffset = 200;
    const int downOffset = 500;
    const int leftOffset = 150;
    const int rightOffset = 150;

    const int d = 10;
    const int hor = 7;
    const int vert = 5;
    const int width = (game->sceneSize().width() -
                       (leftOffset + rightOffset) - d * hor) / hor;
    const int height = (game->sceneSize().height() -
                        (upOffset + downOffset) - d * vert) / vert;

    std::vector<Engy::Entity *> es;

    for (int h = 0; h < hor; ++h) {
        for (int v = 0; v < vert; ++v) {
            QRectF rect(0, 0, width, height);
            auto entity = Engy::Entity::create<Box>(game, rect);
            entity->form()->setPos(leftOffset + width * h + d * h,
                                   upOffset + height * v + d * v);
            es.push_back(entity);
        }
    }

    return es;
}
















