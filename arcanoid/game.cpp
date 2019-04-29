#include "game.hpp"

#include "entity.hpp"
#include "ecarrowkeys.hpp"
#include "components/move.hpp"
#include "eccollisions.hpp"


Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , scene_(new QGraphicsScene)
    , timer_(new Timer(this))
    , field_(makeField()) // Create registry with tangible items
{
    setScene(scene_);
    scene_->setSceneRect({{0, 0}, DEF_SIZE});
    setFixedSize(DEF_SIZE + QSize(5, 5)); // To see whole scene
    setBackgroundBrush(QBrush(QPixmap(":/images/hydra.jpg").scaled(size())));

    // Set game update timer
    timer_->start(int(1.0 / FRAME_RATE * 1000));

    // Create player
    auto player = makePlayer();
    auto keyController = new ECArrowKeys(scene_, player);
    double borderWidth = 5;
    keyController->setLBorder(borderWidth);
    keyController->setRBorder(borderWidth);
    entities_.push_back(player);
    field_->addEntity(player);

    // Add bounds
    auto borders = makeBorders(borderWidth);
    std::copy(borders.begin(), borders.end(), std::back_inserter(entities_));
    std::copy(borders.begin(), borders.end(), std::back_inserter(field_->entities()));

    // Create ball
    auto ball = makeBall();
    entities_.push_back(ball);
    field_->addEntity(ball);

    auto move = new Move(timer_);
    move->setV({2.f, 1.f});
    ball->addComponent(ComponentU(move));

    auto collisions = new ECCollisions(scene_, ball, field_, timer_);
    Q_UNUSED(collisions)
}


Game::~Game()
{
    // QGraphicsView doesn't take ownership of scene.
    delete scene_;
}


void Game::launch()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
}


EntityS Game::makePlayer()
{
    assert(scene_);

    auto * platform = new QGraphicsRectItem(QRectF{0, 0, 200, 20});
    platform->setPos({scene_->width() / 2 - platform->boundingRect().width() / 2,
                     scene_->height() - platform->boundingRect().height()});
    QColor color(0xAA00BB);
    platform->setPen({color});
    platform->setBrush({color});

    auto player = makeEntity(scene_);
    player->addForm(platform);
    return player;
}


EntityS Game::makeBall()
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


std::vector<EntityS> Game::makeBorders(double width)
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

    std::vector<EntityS> borders(rects.size());
    for (size_t i = 0; i < borders.size(); ++i) {
        borders[i] = makeEntity(scene_);
        borders[i]->addForm(rects[i]);
    }
    return borders;
}










