/**
  * @file
  */

#pragma once

#include "stdafx.hpp"
#include "game.hpp"
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
class Entity
        : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Factory of entityes.
     * @param game Takes ownership of entity.
     * @return Created entity.
     */
    template <class E = Entity, class... Args>
    static E * create(Game * game, Args && ...args);
    /**
      * Makes components forget about entity to avoid cycle.
      * (components try to delete themselves from entity in dtor)
      */
    virtual ~Entity();

    /**
     * @brief Set name to current entity instance.
     * @param name
     */
    void setName(QString name);
    /**
     * @brief Name getter.
     * @return
     */
    QString name() const;

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
    /**
     * @brief delForm
     * @return true if form was removed, false otherwise.
     */
    bool delForm();
    QGraphicsItem * form();
    QGraphicsItem const * form() const;
    /**
     * @brief Makes entity forget about form.
     * @return Entity form.
     */
    QGraphicsItem * extractForm();

    /**
     * @brief Entity will emit "keyPressed" signal
     */
    void setFocus();
    bool hasFocus() const;

    /**
     * @brief Entity gets ownership of component. Entity can have only one
     * instance of a component type. If component of incoming type alredy exists,
     * replaces old with new one.
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
    Component * findComponent(Component::Id id);

    /**
     * @brief Finds component of specific type.
     * @return Pointer to component if exists, nullptr otherwise.
     */
    template <class C> C *  findComponent();
    template <class C> bool removeComponent();

signals:
    void formAdded();
    void formChanged();
    void keyPressed(QKeyEvent * event);

protected:
    /**
     * @brief Entity instance can only be created via factory.
     * @param game Takes ownership of entity.
     */
    explicit Entity(Game * game);

private slots:
    void gameDeleted();

private:
    /// Access to delGame
    friend class Game;
    /**
     * @brief delGame Makes entity forget about parent.
     */
    void delGame();
    friend class Component;
    /**
     * @brief Removes componet without deletion
     */
    void forgetComponent(Component::Id id);

    void deleteComponent(Component * c) const;

private:
    class FocusHandler;

    QString name_;

    Game * game_;
    QGraphicsItem * form_ = nullptr;
    FocusHandler  * fh_; // TODO init
    std::unordered_map<Component::Id, Component *> components_;
};


class Entity::FocusHandler final
        : public QGraphicsObject {
    Q_OBJECT

    friend class Entity;
    FocusHandler();

signals:
    void keyPressed(QKeyEvent * event);

private:
    void keyPressEvent(QKeyEvent * event) override;

    // Unused
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) final;
    QRectF boundingRect() const final;
};


template <class E, class... Args>
E * Entity::create(Game * game, Args && ...args) {
    static_assert (std::is_base_of_v<Entity, E>,
                   "E should be derived from entity");
    assert(game);
    auto entity = new E(game, std::forward<Args>(args)...);
    game->addEntity(entity);
    return entity;
}


template <class C>
C * Entity::findComponent() {
    if (auto search = findComponent(Component::id<C>())) {
        auto component = dynamic_cast<C *>(search);
        assert(component);
        return component;
    }
    return nullptr;
}


template <class C>
bool Entity::removeComponent() {
    return removeComponent(Component::id<C>());
}


#define ENGY_CREATABLE_ENTITY \
    template <class E, class... Args> \
    friend E * Entity::create(Game * game, Args && ...args);
#define engy_entity_ctor ENGY_HEAP_ONLY_CONSTRUCTIBLE

} // Engy



