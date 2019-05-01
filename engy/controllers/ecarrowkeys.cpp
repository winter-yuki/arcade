#include "ecarrowkeys.hpp"

#include "game.hpp"


namespace Engy
{

ECArrowKeys::ECArrowKeys(Game * game, EntityW entity)
    : Controller(game, entity)
{
    assert(game);
    assert(!entity.expired());
    assert(ifHasForm(entity));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    /// @warning It should be return statement after emitting "entityDeleted".
    connect(this, &ECArrowKeys::entityDeleted, this, &ECArrowKeys::harakiri);
}


void ECArrowKeys::setDx(OptD dx)
{
    dx_ = dx;
}


ECArrowKeys::OptD ECArrowKeys::dx() const
{
    return dx_;
}


void ECArrowKeys::setDy(OptD dy)
{
    dy_ = dy;
}


ECArrowKeys::OptD ECArrowKeys::dy() const
{
    return dy_;
}


void ECArrowKeys::setLBorder(OptD x)
{
    lborder_ = x;
}


ECArrowKeys::OptD ECArrowKeys::lborder() const
{
    return lborder_;
}


void ECArrowKeys::setRBorder(OptD x)
{
    if (x){
        rborder_ = game()->scene()->width() - x.value();
    } else {
        rborder_ = std::nullopt;
    }
}


ECArrowKeys::OptD ECArrowKeys::rborder() const
{
    return rborder_;
}


void ECArrowKeys::setTBorder(OptD x)
{
    tborder_ = x;
}


ECArrowKeys::OptD ECArrowKeys::tborder() const
{
    return tborder_;
}


void ECArrowKeys::setBBorder(OptD x)
{
    if (x) {
        bborder_ = game()->scene()->height() - x.value();
    } else {
        bborder_ = std::nullopt;
    }
}


ECArrowKeys::OptD ECArrowKeys::bborder() const
{
    return bborder_;
}


void ECArrowKeys::keyPressEvent(QKeyEvent * event)
{
    auto e = entity().lock();
    if (!e) {
        emit entityDeleted();
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        if (auto pnew = left(e)) {
            e->form()->setPos(pnew.value());
        }
        break;

    case Qt::Key_Right:
        if (auto pnew = right(e)) {
            e->form()->setPos(pnew.value());
        }
        break;

    case Qt::Key_Up:
        if (auto pnew = up(e)) {
            e->form()->setPos(pnew.value());
        }
        break;

    case Qt::Key_Down:
        if (auto pnew = down(e)) {
            e->form()->setPos(pnew.value());
        }
        break;
    }
}


std::optional<QPointF> ECArrowKeys::left(EntityS e) const
{
    if (dx_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() - QPointF(dx_.value(), 0);

    if (lborder_.has_value() && npos.x() < lborder_) {
        return { QPointF(lborder_.value(), npos.y()) };
    }
    return npos;
}


std::optional<QPointF> ECArrowKeys::right(EntityS e) const
{
    if (dx_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() + QPointF(dx_.value(), 0);
    auto width = e->form()->boundingRect().width();

    if (rborder_.has_value() && npos.x() + width > rborder_) {
        return { QPointF(rborder_.value() - width, npos.y()) };
    }
    return npos;
}


std::optional<QPointF> ECArrowKeys::up(EntityS e) const
{
    if (dy_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() - QPointF(0, dy_.value());

    if (tborder_.has_value() && npos.y() < tborder_) {
        return { QPointF(npos.x(), tborder_.value()) };
    }
    return npos;
}


std::optional<QPointF> ECArrowKeys::down(EntityS e) const
{
    if (dy_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() + QPointF(0, dy_.value());
    auto height = e->form()->boundingRect().height();

    if (bborder_.has_value() && npos.y() + height > bborder_) {
        return { QPointF(npos.x(), bborder_.value() - height) };
    }
    return npos;
}

} // Engy

























