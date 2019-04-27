#include "controller.hpp"


Controller::Controller(QGraphicsScene * scene, EntityP entity)
    : scene_ (scene)
    , entity_(entity)
{
    assert(scene);
    scene->addItem(this);
}


QGraphicsScene * Controller::scene()
{
    return scene_;
}


EntityP Controller::entity()
{
    return entity_;
}


void Controller::paint(QPainter * painter,
                       QStyleOptionGraphicsItem const * option, QWidget * widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


QRectF Controller::boundingRect() const
{
    return { 0, 0, 0, 0 };
}












