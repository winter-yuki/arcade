#pragma once

#include "stdafx.hpp"


namespace Engy
{

class Entity;

class Component
        : boost::noncopyable {
public:
    using Id = std::type_index;

    // WARNING: Do not delete component manually
    // if it is already added to entity
    virtual ~Component() = default;
    virtual Id id() const = 0;
    Entity * entity();

    template <class T>
    static Id id() { return Id(typeid (typename std::remove_pointer<T>::type)); }

    // To provide for Entity access to entity setter
    friend class Entity;

private:
    void setEntity(Entity * e);

private:
    Entity * entity_ = nullptr;
};


using ComponentU = std::unique_ptr<Component>;

} // Engy
