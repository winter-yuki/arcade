/**
  * @file
  */

#include "ecarrowkeys.hpp"

#include "game.hpp"


namespace Engy
{

ECArrowKeys::ECArrowKeys(EntityW entity)
    : Controller(entity)
{
    assert(ifHasForm(entity));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    connect(game(), &Game::sceneResized, this, &ECArrowKeys::sceneResized);
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
    auto e = entity();
    if (!e) {
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        e->form()->setPos(left(e));
        break;

    case Qt::Key_Right:
        e->form()->setPos(right(e));
        break;

    case Qt::Key_Up:
        e->form()->setPos(up(e));
        break;

    case Qt::Key_Down:
        e->form()->setPos(down(e));
        break;
    }
}


void ECArrowKeys::sceneResized()
{
    setRBorder(rborder_);
    setBBorder(bborder_);
}


QPointF ECArrowKeys::left(EntityS & e) const
{
    if (dx_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() - QPointF(dx_.value(), 0);

    if (lborder_.has_value() && npos.x() < lborder_) {
        return QPointF(lborder_.value(), npos.y());
    }
    return npos;
}


QPointF ECArrowKeys::right(EntityS & e) const
{
    if (dx_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->scenePos() + QPointF(dx_.value(), 0);
    auto width = e->form()->boundingRect().width();

    if (rborder_.has_value() && npos.x() + width > rborder_) {
        return QPointF(rborder_.value() - width, npos.y());
    }
    return npos;
}


QPointF ECArrowKeys::up(EntityS & e) const
{
    if (dy_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() - QPointF(0, dy_.value());

    if (tborder_.has_value() && npos.y() < tborder_) {
        return QPointF(npos.x(), tborder_.value());
    }
    return npos;
}


QPointF ECArrowKeys::down(EntityS & e) const
{
    if (dy_.has_value() == false) {
        return e->form()->pos();
    }

    auto npos = e->form()->pos() + QPointF(0, dy_.value());
    auto height = e->form()->boundingRect().height();

    if (bborder_.has_value() && npos.y() + height > bborder_) {
        return QPointF(npos.x(), bborder_.value() - height);
    }
    return npos;
}

} // Engy

























