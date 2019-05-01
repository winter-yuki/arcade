#pragma once

#include "stdafx.hpp"
#include "components/component.hpp"
#include "entityptrs.hpp"
#include "entityptrs.hpp"


namespace Engy
{

class Game;

/**
 * @brief The Entity class
 */
class Entity final {
public:
    /// Factory
    /**
     * @brief Factory of entityes.
     * @param game Takes ownership of entity.
     * @return Created entity.
     */
    static EntityS create(Game * game);
    ~Entity();

    /**
     * @brief Adds @p form to the scene
     * @param form
     */
    void addForm(QGraphicsItem * form);
    QGraphicsItem * form();

    /// Gets ownership of component
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
    template <class C> C * findComponent();

private:
    /**
     * @brief Entity instance can only be created via factory.
     * @param game Takes ownership of entity.
     */
    explicit Entity(Game * game);

    /// Provides access to forgetComponent()
    friend class Component;
    /**
     * @brief Removes componet without deletion
     */
    void forgetComponent(Component::Id id);

private:
    QGraphicsScene * scene_ = nullptr;
    QGraphicsItem  * form_  = nullptr;
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


inline bool ifHasForm(EntityW const & entity) {
    auto l = entity.lock();
    assert(l);
    return l->form();
}

} // Engy



