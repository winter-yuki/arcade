/**
  * @file
  */

#pragma once

#include "stdafx.hpp"
#include "components/component.hpp"


namespace Engy
{

class Game;

/**
 * @ingroup core
 * @brief Entity, container of componens.
 *
 * Entity should always have game parent.
 * Deletes itself if game deleted and removes itself from game child list
 * on deletion.
 */
class Entity final
        : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Factory of entityes.
     * @param game Takes ownership of entity.
     * @return Created entity.
     */
    static Entity * create(Game * game);
    /**
      * Makes components forget about entity to avoid cycle.
      * (components try to delete themselves from entity in dtor)
      */
    ~Entity();

    /**
     * @brief game
     * @return Pointer to parent game.
     */
    Game * game();
    Game const * game() const;

    /**
     * @brief Adds form to the scene
     * @param form
     */
    void addForm(QGraphicsItem * form);
    void delForm();
    QGraphicsItem * form();
    QGraphicsItem const * form() const;

    /**
     * @brief addComponent Gets ownership of component
     * @param component
     */
    void addComponent(Component * component);
    /**
     * @brief Removes component from entity
     * @return true if element removed, false otherwise
     *
     * Previously makes component forget about parent to break cycle,
     * where component tries delete itself from entity in Component::~Component
     */
    bool removeComponent(Component::Id id);
    std::optional<Component *> findComponent(Component::Id id);

    /**
     * @brief Finds component of specific type.
     * @return Pointer to component if exists, nullptr otherwise.
     */
    template <class C>
    C * findComponent();
    /**
     * @brief Removes componet without deletion
     */
    void forgetComponent(Component::Id id);

private slots:
    void gameDeleted();

private:
    /**
     * @brief Entity instance can only be created via factory.
     * @param game Takes ownership of entity.
     */
    explicit Entity(Game * game);

    /// Access to delGame
    friend class Game;
    /**
     * @brief delGame Makes entity forget about parent.
     */
    void delGame();

private:
    Game * game_;
    QGraphicsItem  * form_ = nullptr;
    std::unordered_map<Component::Id, ComponentU> components_;
};


template <class C>
C * Entity::findComponent() {
    if (auto search = findComponent(Component::id<C>())) {
        auto component = dynamic_cast<C *>(search.value());
        assert(component);
        return component;
    }
    return nullptr;
}

} // Engy



