#include "gamewidget.hpp"

#include <functional>

#include <QDialogButtonBox>

#include "entities.hpp"
#include "components.hpp"
#include "engy/game.hpp"
#include "engy/controllers/ecarrowkeys.hpp"
#include "engy/components/move.hpp"
#include "engy/controllers/eccollisions.hpp"
#include "engy/controllers/collision_handlers.hpp"
#include "engy/controllers/ecscenebounds.hpp"
#include "engy/components/mass.hpp"
#include "engy/components/intangible.hpp"


GameWidget::GameWidget(QWidget * parent)
    : QMainWindow(parent)
{
    createGame();
}


void GameWidget::restartGame()
{
    assert(game_);
    delete game_;
    createGame();
}


void GameWidget::updateScore(int delta)
{
    score_ += delta;
    setWindowTitle(QString("SCORE: %1").arg(score_));
}


void GameWidget::endGame()
{
    // TODO QButtonsDialog with "Restart" and "Exit"
    QApplication::exit();
}


void GameWidget::scoreCounter(Engy::Entity * a, Engy::Entity * b)
{
    if (a->name() == "Ball" && b->name() == "Player") {
        updateScore(10);
    }
}


void GameWidget::createGame()
{
    assert(!game_);
    score_ = 0;
    updateScore(0);

    // Create game
    game_ = new Engy::Game(this);
    game_->setSceneSize({1000, 900});
    game_->setBg(QPixmap(":/images/hydra.jpg").scaled(game_->sceneSize()));
    setFixedSize(game_->size());

    // Create player
    double borderWidth = 5;
    auto player = Engy::Entity::create<Player>(game_);
    auto keyController = Engy::Controller::create<Engy::ECArrowKeys>(player);
    keyController->setDx(25);
    keyController->setDy(std::nullopt);
    keyController->setLBorder(borderWidth);
    keyController->setRBorder(borderWidth);

    // Add bounds
    auto borders = makeBorders(borderWidth);

    // Create field
    auto field = makeField();

    // Create ball
    auto ball = Engy::Entity::create<Ball>(game_);
    ball->form()->moveBy(800, 800);

    auto move = Engy::Component::create<Engy::Move>();
    move->setV({.2f, -0.3f});
    ball->addComponent(move);

    auto collisions = Engy::Controller::create<Engy::ECCollisions>(ball);
    using namespace std::placeholders;
    collisions->setHandler([this](Engy::Entity * a, Engy::Entity * b) {
        Engy::basicCollisionHandler(a, b);
        HP::hpCounter(a, b);
        scoreCounter(a, b);
    });

    auto outOfScene = Engy::Controller::create<Engy::ECSceneBounds>(ball);
    QObject::connect(outOfScene, &Engy::ECSceneBounds::isOut, [outOfScene, this] {
        delete outOfScene->entity();
        endGame();
    });

    // Launch
    game_->launch();
}


std::vector<Engy::Entity *> GameWidget::makeBorders(double width)
{
    assert(game_);

    const qreal gsh = game_->sceneSize().height();
    const qreal gsw = game_->sceneSize().width();

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
        borders[i] = Engy::Entity::create(game_);
        borders[i]->addForm(rects[i]);
        borders[i]->setName(QString("Border %1").arg(i));
    }
    return borders;
}


std::vector<Engy::Entity *> GameWidget::makeField()
{
    assert(game_);

    // TODO components

    const int upOffset = 200;
    const int downOffset = 500;
    const int leftOffset = 150;
    const int rightOffset = 150;

    const int d = 10;
    const int hor = 7;
    const int vert = 5;
    const int width = (game_->sceneSize().width() -
                       (leftOffset + rightOffset) - d * hor) / hor;
    const int height = (game_->sceneSize().height() -
                        (upOffset + downOffset) - d * vert) / vert;

    std::vector<Engy::Entity *> es;

    for (int h = 0; h < hor; ++h) {
        for (int v = 0; v < vert; ++v) {
            QRectF rect(0, 0, width, height);
            auto entity = Engy::Entity::create<Box>(game_, rect);
            entity->form()->setPos(leftOffset + width * h + d * h,
                                   upOffset + height * v + d * v);
            auto hp = Engy::Component::create<HP>();
            entity->addComponent(hp);
            es.push_back(entity);
        }
    }

    // Make moving block
    QRectF rect(0, 0, width + 10, height + 10);
    auto movingBlock = Engy::Entity::create<Box>(game_, rect);
    movingBlock->form()->setPos(leftOffset + width,
                           game_->sceneSize().height() - downOffset + 100);
    es.push_back(movingBlock);

    auto move = Engy::Component::create<Engy::Move>();
    move->setV({.1f, 0});
    movingBlock->addComponent(move);

    auto hp = Engy::Component::create<HP>(500);
    movingBlock->addComponent(hp);

    auto collicions = Engy::Controller::create<Engy::ECCollisions>(movingBlock);
    collicions->setHandler([](Engy::Entity * a, Engy::Entity * b) {
        if (b->name() == "Ball") {
            return;
        }
        Engy::basicCollisionHandler(a, b);
    });

    return es;
}










