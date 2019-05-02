/**
  * @file
  */

/**
  * @defgroup controllers
  * @brief Overseers of entities that can add some interactive to the game.
  */

#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


namespace Engy
{

class Game;

/**
 * @ingroup controllers
 * @brief Base class for any controller in game.
 *
 * By default deletes itself if entity deleted and if game deleted.
 *
 * QGraphicsItem provides key events for derived classes.
 */
class Controller
        : public QGraphicsObject {
    Q_OBJECT

public:
    /**
     * @brief Controller
     * @param game
     * @param entity
     */
    explicit Controller(EntityW entity);
    /**
      * @brief Emits "deleted" signal.
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
    /**
     * @brief Is emitted on dying.
     */
    void deleted();

protected:
    /**
     * @brief deleteControllerOnEntityDeleted
     * @param val If controller should delete itself if entity deleted.
     * @warning It should be "return"  statement in controller method
     * after emitting "entityDeleted" on val == true.
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
