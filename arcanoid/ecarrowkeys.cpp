#include "ecarrowkeys.hpp"


ECArrowKeys::ECArrowKeys(QGraphicsScene * scene, EntityP entity)
    : Controller(scene, entity)
{
    assert(scene);
    assert(entity->form());

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}


void ECArrowKeys::setDx(double dx)
{
    dx_ = dx;
}


double ECArrowKeys::dx() const
{
    return dx_;
}


void ECArrowKeys::setRBorder(double rborder)
{
    rborder_ = scene()->width() - rborder;
}


double ECArrowKeys::rborder() const
{
    return rborder_;
}


void ECArrowKeys::setLBorder(double lborder)
{
    lborder_ = lborder;
}


double ECArrowKeys::lborder() const
{
    return lborder_;
}


void ECArrowKeys::keyPressEvent(QKeyEvent * event)
{
    auto pos = entity()->form()->pos();
    switch (event->key()) {
    case Qt::Key_Left:
        if (pos.x() - dx_ >= lborder_) {
            entity()->form()->setX(pos.x() - dx_);
        } else {
            entity()->form()->setX(lborder_);
        }
        break;

    case Qt::Key_Right:
        auto width = entity()->form()->scale() *
                entity()->form()->boundingRect().width();
        auto rpoint = pos.x() + width;
        if (rpoint + dx_ <= rborder_) {
            entity()->form()->setX(pos.x() + dx_);
        } else {
            entity()->form()->setX(rborder_ - width);
        }
        break;
    }
}














