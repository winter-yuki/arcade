#pragma once

#include "stdafx.hpp"
#include "component.hpp"


class Entity {
public:
    void addComponent(Component * component);
    void removeComponent(Component * component);
    std::optional<Component *> findComponent(Component::Id id);

private:
    std::unordered_map<Component::Id, Component *> components_;
};


using EntityP = std::unique_ptr<Entity>;
