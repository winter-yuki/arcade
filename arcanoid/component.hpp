#pragma once

#include "stdafx.hpp"


class Component
        : boost::noncopyable {
public:
    using Id = std::type_index;

    Component()          = default;
    virtual ~Component() = default;

    Id getId() const;
};



