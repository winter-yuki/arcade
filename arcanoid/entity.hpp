#pragma once

#include "stdafx.hpp"
#include "component.hpp"


class Entity final {
public:
    explicit Entity(QGraphicsScene * scene);

    void addForm(QGraphicsItem * form);
    QGraphicsItem * form();

    void addComponent(Component * component);
    void removeComponent(Component * component);
    std::optional<Component *> findComponent(Component::Id id);

private:
    QGraphicsScene * scene_;

    QGraphicsItem * form_ = nullptr;

    std::unordered_map<Component::Id, Component *> components_;
};


using EntityP = std::shared_ptr<Entity>;
inline EntityP makeEntity(QGraphicsScene * scene) {
    return std::make_shared<Entity>(scene);
}
