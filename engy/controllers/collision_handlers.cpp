#include "collision_handlers.hpp"

#include "stdafx.hpp"
#include "eccollisions.hpp"
#include "components/mass.hpp"
#include "components/move.hpp"


namespace Engy
{

namespace
{
std::optional<QVector2D> getNormalOfBoundingRect(EntityS & a, EntityS & b);
}


void basicCollisionHandler(EntityS & a, EntityS & b)
{
//    static_assert (std::is_same<std::function<decltype(basicCollisionHandler)>,
//                   ECCollisions::Handler>::value);
    assert(a && b);
    assert(a->form() && b->form());

    auto move = a->findComponent<Move>();
    if (!move) {
        qDebug() << "Move component of tracked object has not found";
        return;
    }
    QVector2D v = move->v();

    if (auto n = getNormalOfBoundingRect(a, b)) {
        assert(!n.value().isNull());
        assert(std::abs(n.value().length() - 1) < 1e-8f);

        // Count speed vector after bounce
        auto newV = v - 2 * (v * n.value()) * n.value();
        assert(abs(newV.length() - v.length()) < 1e-8f);

        move->setV(newV);

    } else {
        qDebug() << "Collision detection isn't in time,"
                    "object is already in figure";
        move->setV(-v);
    }
}


namespace
{

std::optional<QVector2D> getNormalOfBoundingRect(EntityS & a, EntityS & b)
{
    const auto pos  = a->form()->pos();
    const auto aabb = b->form()->boundingRect();

    // Determine side which a collided with

    // From the left
    if (pos.x() <= aabb.left()) {
        return { QVector2D(-1, 0) };
    }
    // From the right
    if (pos.x() >= aabb.right()) {
        return { QVector2D(1, 0) };
    }

    // From the top
    if (pos.y() <= aabb.top()) {
        return { QVector2D(0, -1) };
    }
    // From the bottom
    if (pos.y() >= aabb.bottom()) {
        return { QVector2D(0, 1) };
    }

    // Figure is alredy inside the box
    return std::nullopt;
}

}

} // Engy







