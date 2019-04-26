#include "game.hpp"

#include "entity.hpp"
#include "border.hpp"


Game::Game(QWidget * parent)
    : QGraphicsView(parent)
    , scene_(new QGraphicsScene)
{
    setScene(scene_);
    scene_->setSceneRect(0, 0, DEF_SIZE.width(), DEF_SIZE.height());
    setFixedSize(DEF_SIZE);

    // Create platform
    player_ = new Platform;
    double playerScale = 5;
    player_->setScale(playerScale);
    player_->setPos(scene_->width() / 2 - playerScale * player_->boundingRect().width() / 2,
                    scene_->height() - playerScale * player_->boundingRect().height());
    player_->setFlag(QGraphicsItem::ItemIsFocusable);
    player_->setFocus();
    scene_->addItem(player_);

    // Add bounds
    QColor borderColor(QRgb(0x00AA00));
    double borderWidth = 5;
    std::array bounds = {
        new (std::nothrow) Border(QRectF{0, 0, borderWidth, scene_->height()}),
        new (std::nothrow) Border(QRectF{0, 0, scene_->width(), borderWidth}),
        new (std::nothrow) Border(QRectF{scene_->width() - borderWidth, 0,
                                         borderWidth, scene_->height()})
    };

    for (auto bound : bounds) {
        if (!bound) {
            throw std::runtime_error(""); // TODO error processing
        }
        bound->setBrush(QBrush(borderColor));
        bound->setPen(QPen(borderColor));
        scene_->addItem(bound);
    }
}


void Game::launch()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    show();
}






