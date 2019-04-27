#include "ecarrowkeys.hpp"


ECArrowKeys::ECArrowKeys(QGraphicsScene * scene, EntityP entity)
    : scene_ (scene)
    , entity_(entity)
{
    assert(scene_);
    assert(entity_->form());

    scene_->addItem(this);
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
    rborder_ = scene_->width() - rborder;
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
    auto pos = entity_->form()->pos();
    switch (event->key()) {
    case Qt::Key_Left:
        if (pos.x() - dx_ >= lborder_) {
            entity_->form()->setX(pos.x() - dx_);
        } else {
            entity_->form()->setX(lborder_);
        }
        break;

    case Qt::Key_Right:
        auto width = entity_->form()->boundingRect().width() * entity_->form()->scale();
        auto rpoint = pos.x() + width;
        if (rpoint + dx_ <= rborder_) {
            entity_->form()->setX(pos.x() + dx_);
        } else {
            entity_->form()->setX(rborder_ - width);
        }
        break;
    }
}


void ECArrowKeys::paint(QPainter * painter,
                        QStyleOptionGraphicsItem const * option, QWidget * widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


QRectF ECArrowKeys::boundingRect() const
{
    return { 0, 0, 0, 0 };
}














