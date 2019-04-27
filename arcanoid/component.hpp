#pragma once

#include "stdafx.hpp"


// TODO form of component
class Component
        : boost::noncopyable {
public:
    using Id = std::type_index;

    Component()          = default;
    virtual ~Component() = default;

    Id getId() const;
};


#define GET_ID(componentType) Component::Id(typeid (componentType))
