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

    explicit Component(Id id);
    virtual ~Component(); ///< Deletes itself from parent manually

    Id id() const;
    Entity * entity();

    template <class T>
    static Id id() { return Id(typeid (typename std::remove_pointer<T>::type)); }

    // Provide for Entity access to setEntity
    friend class Entity;

signals:
    void entitySetted();

private:
    void setEntity(Entity * e);
    void delEntity(); ///< Removes reference to entity

private:
    Id id_;
    Entity * entity_ = nullptr;
};

using ComponentU = std::unique_ptr<Component>;

} // Engy
