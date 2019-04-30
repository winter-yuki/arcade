#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


namespace Engy
{

class Game;

class Controller
        : public QGraphicsObject { // Provides key events for derived classes
    Q_OBJECT

public:
    Controller(Game * game, EntityW entity);

    Game * game();
    EntityW entity();

    // Unused
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;
    QRectF boundingRect() const override;

public slots:
    void harakiri();

signals:
    void entityDeleted();

private:
    Game *  game_;
    EntityW entity_;
};

} // Engy
