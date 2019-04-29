#pragma once

#include "stdafx.hpp"
#include "entityptrs.hpp"


class Component
        : boost::noncopyable {
public:
    using Id = std::type_index;

    virtual ~Component() = default;
    Id getId() const;
    Entity * entity();

    // To provide for Entity access to entity setter
    friend class Entity;

private:
    void setEntity(Entity * e);

private:
    Entity * entity_ = nullptr;
};

using ComponentU = std::unique_ptr<Component>;

#define GET_ID(componentType) Component::Id(typeid (componentType))
