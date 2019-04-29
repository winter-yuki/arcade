#include "controller.hpp"


namespace Engy
{

Controller::Controller(QGraphicsScene * scene, EntityW e)
    : scene_ (scene)
    , entity_(e)
{
    assert(scene);
    assert(!e.expired());
    scene->addItem(this);
}


QGraphicsScene * Controller::scene()
{
    return scene_;
}


EntityW Controller::entity()
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


void Controller::harakiri()
{
    delete this;
}

}







