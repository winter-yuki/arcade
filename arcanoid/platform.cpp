#include "platform.hpp"


Platform::Platform(QGraphicsPixmapItem * parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/player.png"));
}


void Platform::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) { // TODO repos value
    case Qt::Key_Left:
        setPos({x() - dx_, y()});
        break;
    case Qt::Key_Right:
        setPos({x() + dx_, y()});
        break;
    }
}
