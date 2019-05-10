#include "basiccollisionhandler.hpp"

#include "entity.hpp"
#include "move.hpp"


namespace Engy
{

Collisions::Handler BasicCollisionHandler::handler() const
{
    return reflectionHandler;
}


void BasicCollisionHandler::reflectionHandler(Entity * a, Entity * b)
{
    assert(a && b);

    if (!a->form() || !b->form()) {
        return;
    }

    if (a->findComponent<DisReflector>() ||
            b->findComponent<DisReflector>()) {
        return;
    }

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
        assert(std::abs(newV.length() - v.length()) < 1e-8f);
        move->setV(newV);

    } else {
        qDebug() << "Collision detection isn't in time,"
                    "object is already in figure";
        move->setV(-v);
        move->update(10 * UPDATE_INTERVAL); // Move entity back slightly
    }
}


std::optional<QVector2D>
BasicCollisionHandler::getNormalOfBoundingRect(Entity const * a, Entity const * b)
{
    const auto abr = a->form()->boundingRect();
    const auto pos = a->form()->pos() + QPointF(abr.width(), abr.height()) / 2;

    const auto aabb = [&b]() -> QRectF {
            const auto bpos = b->form()->pos();
            auto rect = b->form()->boundingRect();
            rect.moveTo(bpos.x(), bpos.y());
            return rect; } ();

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

} // Engy
