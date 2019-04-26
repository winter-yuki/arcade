#include "render.hpp"


Render::Render(QGraphicsScene * scene, QGraphicsItem * parent)
    : QGraphicsItem(parent)
    , scene_(scene)
{
    assert(scene_);
    scene_->addItem(this);
}


Render::~Render()
{
    scene_->removeItem(this);
}


QRectF Render::boundingRect() const
{
    return { 0, 0, 10, 10 };
}


void Render::paint(QPainter * painter,
                   QStyleOptionGraphicsItem const * option, QWidget * widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

//    if (painter_) {
//        painter_(painter);
//    }
    painter->drawRect(QRectF{10, 50, 100, 500});
}
