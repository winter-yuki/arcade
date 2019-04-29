#pragma once

#include "stdafx.hpp"
#include "components/component.hpp"


class Entity final {
public:
    explicit Entity(QGraphicsScene * scene);

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
    QGraphicsScene * scene_;
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


#include "entityptrs.hpp"

inline EntityS makeEntity(QGraphicsScene * scene) {
    return std::make_shared<Entity>(scene);
}







