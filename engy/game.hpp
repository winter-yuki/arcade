/**
  * @file
  */

/**
  * @mainpage Wow!
  */

/**
  * @defgroup core Core
  */

#pragma once

#include "stdafx.hpp"
#include "timer.hpp"


namespace Engy
{

class Entity;

/**
 * @ingroup core
 * @brief The Game class
 *
 * It doesn't use smart pointer because immidiate entity deletion is required.
 * It is hard to manage quantity of shared poiters, and set is used, so
 * it is hard to use unique poiters.
 */
class Game final
        : public QGraphicsView {
    Q_OBJECT

public:
    explicit Game(QWidget * parent = nullptr);
    ~Game();

    /**
     * @brief launch Launches game cycle. And shows widget.
     */
    void launch();

    /**
     * @brief setFrameRate
     * @param fr frame rate
     *
     * Works until game is not lauched.
     */
    void setFrameRate(int64_t fr);
    int64_t frameRate() const;
    void setSceneSize(QSize size);
    QSize sceneSize() const;
    void setBg(QBrush b);

    Timer *       timer();
    Timer const * timer() const;
    QGraphicsScene       * scene();
    QGraphicsScene const * scene() const;

    auto const & entities() const { return es_; }

public slots:
    /**
     * @brief removeEntity Deletes entity.
     * @param entity Child entity to delete.
     * @return If entity was deleted.
     */
    bool removeEntity(Entity * entity);

signals:
    void sceneResized();

private:
    /// Admit entity to add and detach itself from the game.
    friend class Entity;
    /**
     * @brief addEntity Game takes ownershop of entity.
     * @param entity Child entity.
     * @return If entity was added.
     */
    bool addEntity(Entity * entity);
    /**
     * @brief forgetEntity Breaks ownership without deletion of entity.
     * @param entity Child entity.
     * @return If entity was forgotten.
     */
    bool forgetEntity(Entity * entity);

private:
    int64_t frameRate_ = 60;
    QSize sceneSize_ = { 720, 720 };

    Timer          * timer_;
    QGraphicsScene * scene_;
    std::unordered_set<Entity *> es_;
};

} // Engy
