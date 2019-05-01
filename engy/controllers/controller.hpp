#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


namespace Engy
{

class Game;

/**
 * @brief Base class for any controller in game.
 *
 * By default deletes itself if entity deleted and if game deleted.
 */
class Controller
        : public QGraphicsObject { // Provides key events for derived classes
    Q_OBJECT

public:
    /**
     * @brief Controller
     * @param game
     * @param entity
     */
    Controller(Game * game, EntityW entity);
    /**
      * @brief Disconnects everything from object
      */
    ~Controller() override;

    /**
     * @brief game
     * @return Pointer to game, controller binded with.
     */
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

protected:
    /**
     * @brief deleteControllerOnEntityDeleted
     * @param val If controller should delete itself if entity deleted.
     * @warning It should be "return"  statement in controller method
     * after emitting "entityDeleted" on @p val @p == true.
     */
    void deleteControllerIfEntityDeleted(bool val = true);
    /**
     * @brief deleteControllerIfGameDeleted
     * @param val If controller should delete itself if game deleted.
     */
    void deleteControllerIfGameDeleted(bool val = true);

private:
    Game *  game_;
    EntityW entity_;

    bool deleteControllerIfEntityDeleted_ = false;
    bool deleteControllerIfGameDeleted_   = false;
};

} // Engy
