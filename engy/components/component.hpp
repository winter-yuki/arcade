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

    /**
     * @brief Component factory.
     *
     * Components can only be created on heap.
     */
    template <class C, class... Args>
    static C * create(Args && ...args);

    /**
     * @brief ~Component
     *
     * Deletes itself from parent.
     */
    virtual ~Component();

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

protected:
    explicit Component(Id id);

private:
    void setEntity(Entity * e); ///< Sets reference to entity
    void delEntity();           ///< Removes reference to entity

private:
    Id id_;
    Entity * entity_ = nullptr; ///< Parent
};

using ComponentU = std::unique_ptr<Component>;


template <class C, class... Args>
C * Component::create(Args && ...args) {
    static_assert (std::is_base_of_v<Component, C>,
                   "class T should be component");
    return new C(std::forward(args)...);
}


template <class T>
Component::Id Component::id() {
    static_assert (std::is_base_of_v<Component, T>,
                   "class T should be component");
    return Id(typeid (typename std::remove_pointer<T>::type));
}


#define ENGY_CREARABLE_COMPONENT \
    template <class C, class... Args> \
    friend C * Component::create(Args && ...args);

} // Engy










