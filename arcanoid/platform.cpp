#include "platform.hpp"
#include "border.hpp"


Platform::Platform(QGraphicsPixmapItem * parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/player.png"));
}


void Platform::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        setPos({x() - dx_, y()});
        break;
    case Qt::Key_Right:
        setPos({x() + dx_, y()});
        break;
    }

    auto collisions = collidingItems();
    for (auto item : collisions) {
        if (typeid (*item) == typeid (Border)) { // TODO collisions
            switch (event->key()) {
            case Qt::Key_Left:
                setPos({x() + dx_, y()});
                break;
            case Qt::Key_Right:
                setPos({x() - dx_, y()});
                break;
            }
        }
    }
}
