#include "collision_handlers.hpp"

#include "stdafx.hpp"
#include "eccollisions.hpp"
#include "components/mass.hpp"
#include "components/move.hpp"


namespace
{
QVector2D getNormalOfBoundingRect(EntityS & a, EntityS & b);
}


void basicCollisionHandler(EntityS & a, EntityS & b)
{
    static_assert (std::is_same<std::function<decltype(basicCollisionHandler)>,
                   ECCollisions::Handler>::value);
    assert(a && b);
    assert(a->form() && b->form());

    auto move = a->findComponent<Move>();
    if (!move) {
        qDebug() << "Move component of tracked object has not found";
        return;
    }
    QVector2D v = move->v();

    auto n = getNormalOfBoundingRect(a, b);
    assert(!n.isNull());
    assert(std::abs(n.length() - 1) < 1e-8f);

    auto newV = v - 2 * (v * n) * n;
    assert(abs(newV.length() - v.length()) < 1e-8f);

    move->setV(newV);
}


namespace
{

QVector2D getNormalOfBoundingRect(EntityS & a, EntityS & b)
{
    auto pos  = a->form()->pos();
    auto aabb = b->form()->boundingRect();

    // Determine side which a collided with

    // From the left
    if (pos.x() <= aabb.left()) {
        return { -1, 0 };
    }
    // From the right
    if (pos.x() >= aabb.right()) {
        return { 1, 0 };
    }

    // From the top
    if (pos.y() <= aabb.top()) {
        return { 0, -1 };
    }
    // From the bottom
    if (pos.y() >= aabb.bottom()) {
        return { 0, 1 };
    }

    // Figure is alredy inside the box
    // TODO
    assert(false);
}

}









