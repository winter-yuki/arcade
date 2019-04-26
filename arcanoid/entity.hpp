#pragma once

#include "stdafx.hpp"

#include "component.hpp"


class Entity final {
public:
    void addComponent(Component * component);
    void removeComponent(Component * component);
    std::optional<Component *> findComponent(Component::Id id);

private:
    std::unordered_map<Component::Id, Component *> components_;
};
