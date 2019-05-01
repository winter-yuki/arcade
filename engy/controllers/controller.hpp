#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


namespace Engy
{

class Game;

/**
 * @brief Base class for any controller in game.
 */
class Controller
        : public QGraphicsObject { // Provides key events for derived classes
    Q_OBJECT

public:
    Controller(Game * game, EntityW entity);

    Game * game();
    /**
     * @brief entuty
     * @return Shared pointer to entity.
     * If pointer is empty, emits "entityDeleted" and returnes empty sharded.
     */
    EntityS entity();

    // Unused
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;
    QRectF boundingRect() const override;

public slots:
    /**
     * @brief harakiri Controller deletes itself.
     */
    void harakiri();

signals:
    /**
     * @brief entityDeleted
     */
    void entityDeleted();

private:
    Game *  game_;
    EntityW entity_;
};

} // Engy
