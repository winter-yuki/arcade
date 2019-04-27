#pragma once

#include "stdafx.hpp"
#include "component.hpp"


class Entity final {
public:
    explicit Entity(QGraphicsScene * scene);

    void addForm(QGraphicsItem * form);
    QGraphicsItem * form();

    void addComponent(Component * component);
    void addComponent(ComponentP  component);
    void removeComponent(Component::Id id);
    std::optional<Component *> findComponent(Component::Id id);

private:
    QGraphicsScene * scene_;
    QGraphicsItem  * form_ = nullptr;
    std::unordered_map<Component::Id, ComponentP> components_;
};


using EntityP = std::shared_ptr<Entity>;
inline EntityP makeEntity(QGraphicsScene * scene) {
    return std::make_shared<Entity>(scene);
}
