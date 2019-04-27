#include "game.hpp"

#include "entity.hpp"
#include "ecarrowkeys.hpp"


Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , scene_(new QGraphicsScene)
{
    setScene(scene_);
    scene_->setSceneRect({{0, 0}, DEF_SIZE});
    setFixedSize(DEF_SIZE + QSize(5, 5));

    auto backgroundImage = QPixmap(":/images/hydra.jpg").scaledToHeight(height());
    setBackgroundBrush(QBrush(backgroundImage));


    double borderWidth = 5;

    // Create player
    auto player = makePlayer();
    auto * keyController = new ECArrowKeys(scene_, player);
    keyController->setLBorder(borderWidth);
    keyController->setRBorder(borderWidth);
    entities_.push_back(player);

    // Add bounds
    auto borders = makeBorders(borderWidth);
    std::move(borders.begin(), borders.end(), std::back_inserter(entities_));

    // Create ball TODO
    auto ball = makeBall();
    entities_.push_back(ball);
}


void Game::launch()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
}


EntityP Game::makePlayer()
{
    assert(scene_);

    auto * platform = new QGraphicsPixmapItem;
    platform->setPixmap(QPixmap(":/images/player.png"));
    double scale = 5;
    platform->setScale(scale);
    platform->setPos(scene_->width() / 2 - scale * platform->boundingRect().width() / 2,
                     scene_->height() - scale * platform->boundingRect().height());

    auto player = makeEntity(scene_);
    player->addForm(platform);
    return player;
}


EntityP Game::makeBall()
{
    QColor ballColor(QRgb(0x00AADD));

    auto * ball = new QGraphicsEllipseItem;
    ball->setRect({100, 100, 50, 50});
    ball->setBrush(QBrush(ballColor));
    ball->setPen(QPen(ballColor));

    auto entity = makeEntity(scene_);
    entity->addForm(ball);
    return entity;
}


std::vector<EntityP> Game::makeBorders(double width)
{
    QColor borderColor(QRgb(0x00AA00));
    std::array rects = {
        new QGraphicsRectItem(QRectF{0, 0, width, scene_->height()}),
        new QGraphicsRectItem(QRectF{0, 0, scene_->width(), width}),
        new QGraphicsRectItem(QRectF{scene_->width() - width, 0,
                                     width, scene_->height()})
    };

    for (auto rect : rects) {
        rect->setBrush(QBrush(borderColor));
        rect->setPen(QPen(borderColor));
    }

    std::vector<EntityP> borders(rects.size());
    for (size_t i = 0; i < borders.size(); ++i) {
        borders[i] = makeEntity(scene_);
        borders[i]->addForm(rects[i]);
    }
    return borders;
}










