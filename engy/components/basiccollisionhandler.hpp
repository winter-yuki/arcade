#pragma once

#include "collisions.hpp"


namespace Engy
{

/**
 * @ingroup component
 */
class BasicCollisionHandler final
        : public CollisionHandlerT<BasicCollisionHandler> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        BasicCollisionHandler() = default;

public:
    Collisions::Handler handler() const override;

    static void reflectionHandler(Entity * a, Entity * b);
    static std::optional<QVector2D>
    getNormalOfBoundingRect(Entity const * a, Entity const * b);
};

} // Engy
