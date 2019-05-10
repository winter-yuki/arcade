#include "controllers.hpp"

#include <cassert>


SpaceButton::SpaceButton(Engy::Entity * e, std::function<void (void)> handler)
    : Engy::Controller(e)
    , h_(handler)
{
    assert(handler);
    connect(e, &Engy::Entity::keyPressed, this, &SpaceButton::keyPressed);
}


void SpaceButton::keyPressed(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Space) {
        h_();
    }
}
