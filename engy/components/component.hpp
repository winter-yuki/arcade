/**
  * @file
  * @brief Component base class.
  */

/**
  * @defgroup component Components
  * @brief Contains components.
  *
  * Components add specific bahaviour to entities.
  * They contain come date, and refence to parent entity to work with.
  */

#pragma once

#include "stdafx.hpp"


namespace Engy
{

class Entity;

/**
 * @ingroup component
 * @brief Base class for all components in game.
 */
class Component
        : public QObject {
    Q_OBJECT

public:
    using Id = std::type_index;

    explicit Component(Id id);
    virtual ~Component(); ///< Deletes itself from parent manually

    Id id() const;
    Entity * entity();

    /**
     * @param T Can be component type or pointer.
     * @return Id of component.
     */
    template <class T>
    static Id id();

    /// Provide for Entity access to setEntity
    friend class Entity;

signals:
    void entitySetted();

private:
    void setEntity(Entity * e); ///< Sets reference to entity
    void delEntity();           ///< Removes reference to entity

private:
    Id id_;
    Entity * entity_ = nullptr; ///< Parent
};

using ComponentU = std::unique_ptr<Component>;


template <class T>
Component::Id Component::id() {
    static_assert (std::is_base_of_v<Component, T>,
                   "class T should be component");
    return Id(typeid (typename std::remove_pointer<T>::type));
}

} // Engy
