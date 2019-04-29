#include "ecarrowkeys.hpp"


ECArrowKeys::ECArrowKeys(QGraphicsScene * scene, EntityW entity)
    : Controller(scene, entity)
{
    assert(scene);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // It should be return statement after emitting "entityDeleted"
    connect(this, &ECArrowKeys::entityDeleted, this, &ECArrowKeys::harakiri);
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
    auto e = entity().lock();
    if (!e) {
        emit entityDeleted();
        return;
    }

    auto pos = e->form()->pos();
    switch (event->key()) {
    case Qt::Key_Left:
        if (pos.x() - dx_ >= lborder_) {
            e->form()->setX(pos.x() - dx_);
        } else {
            e->form()->setX(lborder_);
        }
        break;

    case Qt::Key_Right:
        auto width = e->form()->scale() * e->form()->boundingRect().width();
        auto rpoint = pos.x() + width;
        if (rpoint + dx_ <= rborder_) {
            e->form()->setX(pos.x() + dx_);
        } else {
            e->form()->setX(rborder_ - width);
        }
        break;
    }
}









