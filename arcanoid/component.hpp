#pragma once

#include "stdafx.hpp"


class Entity;

class Component
        : boost::noncopyable {
public:
    using Id = std::type_index;

    explicit Component(Entity * owner);
    virtual ~Component() = default;

    Id getId() const;

    Entity * entity();

private:
    Entity * entity_;
};

using ComponentP = std::unique_ptr<Component>;

#define GET_ID(componentType) Component::Id(typeid (componentType))
