#include "game.hpp"

#include "entity.hpp"


Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , scene_(new QGraphicsScene)
{
    setScene(scene_);
    scene_->setSceneRect(0, 0, DEF_SIZE.width(), DEF_SIZE.height());
    setFixedSize(DEF_SIZE);

    player_ = new Platform;
    double playerScale = 5;
    player_->setScale(playerScale);
    player_->setPos(scene_->width() / 2 - playerScale * player_->boundingRect().width() / 2,
                    scene_->height() - playerScale * player_->boundingRect().height());
    player_->setFlag(QGraphicsItem::ItemIsFocusable);
    player_->setFocus();
    scene_->addItem(player_);
}


void Game::launch()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
}






