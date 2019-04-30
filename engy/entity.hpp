#pragma once

#include "stdafx.hpp"
#include "components/component.hpp"
#include "entityptrs.hpp"
#include "entityptrs.hpp"


namespace Engy
{

class Game;

class Entity final {
public:
    // Factory
    static EntityS create(Game * game);
    ~Entity();

    // Also adds item to the scene
    void addForm(QGraphicsItem * form);
    QGraphicsItem * form();

    // Gets ownership of component
    void addComponent(ComponentU component);
    void removeComponent(Component::Id id);
    std::optional<Component *> findComponent(Component::Id id);

    // Returnes pointer to component if exists, nullptr otherwise.
    template <class C> C * findComponent();

private:
    explicit Entity(Game * game);

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

} // Engy



