#include "game.hpp"

#include "entity.hpp"
#include "render.hpp"


Game::Game(QWidget * parent)
    : QGraphicsView(parent)
{
    scene_ = new QGraphicsScene;

    setScene(scene_);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWinSize(DEF_SIZE);

    // TODO
//    player_ = new Entity;
//    auto view = new Render(scene_);
//    view->setFlag(QGraphicsItem::ItemIsFocusable);
//    view->setFocus();
//    player_->addComponent(view);
}


void Game::setWinSize(QSize size)
{
    assert(scene_);
    scene_->setSceneRect(0, 0, size.width(), size.height());
    setFixedSize(size);
}


void Game::launch()
{
    show();
}
