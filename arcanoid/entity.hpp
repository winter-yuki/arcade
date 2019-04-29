#pragma once

#include "stdafx.hpp"
#include "component.hpp"


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

private:
    QGraphicsScene * scene_;
    QGraphicsItem  * form_ = nullptr;
    std::unordered_map<Component::Id, ComponentU> components_;
};


#include "entityptrs.hpp"

inline EntityS makeEntity(QGraphicsScene * scene) {
    return std::make_shared<Entity>(scene);
}







