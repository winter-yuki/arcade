/**
  * @file
  */

#pragma once

#include "engy/components/component.hpp"


namespace Engy
{

/**
 * @ingroup component
 * @brief
 */
class Collisions final
        : public ComponentT<Collisions> {
    Q_OBJECT
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        Collisions(int checkingInterval = 15 /*60 fps*/);

public:
    /**
     * 1st: given entity, 2nd: other entity from field.
     * Shared poiners are guaranted not to be empty.
     */
    using Handler = std::function<void (Entity *, Entity *)>;

    void addHandler(Component::Id handler);
    /**
     * @brief Also adds handler to entity if Collisions
     * is already added to entity.
     * @param handler
     */
    void addHandler(Component * handler);
    void addHandlers(std::initializer_list<Component::Id> l);
    /**
     * @brief Also adds handlers to entity if Collisions
     * is already added to entity.
     * @param l
     */
    void addHandlers(std::initializer_list<Component *> l);
    void rmHandler(Component::Id id);

private:
    void timerEvent(QTimerEvent * event) override;
    void applyHandlers(Entity * a, Entity * b);

private:
    std::vector<Component::Id> hs_;
};


/**
 * @ingroup component
 * @brief Base class for all collision handlers.
 */
class CollisionHandler
        : public Component {
public:
    virtual Collisions::Handler handler() const = 0;

protected:
    explicit CollisionHandler(Component::Id id);
};


/**
 * @ingroup component
 */
template <class H>
class CollisionHandlerT
        : public CollisionHandler {
protected:
    CollisionHandlerT()
        : CollisionHandler(id<H>())
    {}
};


/**
 * @ingroup component
 * @param H should be unique type (type of lambda for example) to
 * identificate this component.
 */
template <class H>
class FunctionHandler final
        : public CollisionHandlerT<FunctionHandler<H>> {
    ENGY_CREATABLE_COMPONENT
    engy_component_ctor:
        explicit FunctionHandler(Collisions::Handler h) : h_(std::move(h)) {}
public:
    Collisions::Handler handler() const override { return h_; }
private:
    Collisions::Handler h_;
};

} // Engy



















