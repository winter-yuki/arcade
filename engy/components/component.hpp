#pragma once

#include "stdafx.hpp"


namespace Engy
{

class Entity;

/**
 * @brief Base class for all components in game.
 */
class Component
        : public QObject
        , boost::noncopyable {
    Q_OBJECT

public:
    using Id = std::type_index;

    /// @warning: Do not delete component manually
    /// if it is already added to an entity.
    virtual ~Component() = default;
    virtual Id id() const = 0;
    Entity * entity();

    template <class T>
    static Id id() { return Id(typeid (typename std::remove_pointer<T>::type)); }

    // Provide for Entity access to setEntity
    friend class Entity;

signals:
    void entitySetted();

private:
    void setEntity(Entity * e);

private:
    Entity * entity_ = nullptr;
};

using ComponentU = std::unique_ptr<Component>;

} // Engy
