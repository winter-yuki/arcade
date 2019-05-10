/**
  * @file
  */

#include "ecarrowkeys.hpp"

#include "game.hpp"


namespace Engy
{

ECArrowKeys::ECArrowKeys(Entity * entity)
    : Controller(entity)
{
    assert(entity);
    connect(game(), &Game::sceneResized, this, &ECArrowKeys::sceneResized);
    connect(entity, &Entity::keyPressed, this, &ECArrowKeys::keyPressed);

    if (!entity->hasFocus()) {
        qDebug() << "ECArrowKeys: tracked entity doesn't have focus";
    }
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


void ECArrowKeys::keyPressed(QKeyEvent * event)
{
    if (!entity()->form()) {
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        entity()->form()->setPos(left());
        break;

    case Qt::Key_Right:
        entity()->form()->setPos(right());
        break;

    case Qt::Key_Up:
        entity()->form()->setPos(up());
        break;

    case Qt::Key_Down:
        entity()->form()->setPos(down());
        break;
    }
}


void ECArrowKeys::sceneResized()
{
    setRBorder(rborder_);
    setBBorder(bborder_);
}


QPointF ECArrowKeys::left() const
{
    assert(entity()->form());

    if (dx_.has_value() == false) {
        return entity()->form()->pos();
    }

    auto npos = entity()->form()->pos() - QPointF(dx_.value(), 0);

    if (lborder_.has_value() && npos.x() < lborder_) {
        return QPointF(lborder_.value(), npos.y());
    }
    return npos;
}


QPointF ECArrowKeys::right() const
{
    assert(entity()->form());

    if (dx_.has_value() == false) {
        return entity()->form()->pos();
    }

    auto npos = entity()->form()->scenePos() + QPointF(dx_.value(), 0);
    auto width = entity()->form()->boundingRect().width();

    if (rborder_.has_value() && npos.x() + width > rborder_) {
        return QPointF(rborder_.value() - width, npos.y());
    }
    return npos;
}


QPointF ECArrowKeys::up() const
{
    assert(entity()->form());

    if (dy_.has_value() == false) {
        return entity()->form()->pos();
    }

    auto npos = entity()->form()->pos() - QPointF(0, dy_.value());

    if (tborder_.has_value() && npos.y() < tborder_) {
        return QPointF(npos.x(), tborder_.value());
    }
    return npos;
}


QPointF ECArrowKeys::down() const
{
    assert(entity()->form());

    if (dy_.has_value() == false) {
        return entity()->form()->pos();
    }

    auto npos = entity()->form()->pos() + QPointF(0, dy_.value());
    auto height = entity()->form()->boundingRect().height();

    if (bborder_.has_value() && npos.y() + height > bborder_) {
        return QPointF(npos.x(), bborder_.value() - height);
    }
    return npos;
}

} // Engy

























