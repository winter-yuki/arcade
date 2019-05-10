#pragma once

#include "engy/controllers/controller.hpp"
#include "engy/entity.hpp"


class SpaceButton final
        : public Engy::Controller {
    ENGY_CREATABLE_CONTROLLER

    engy_controller_ctor:
        explicit SpaceButton(Engy::Entity * e,
                             std::function<void (void)> handler);

private slots:
    void keyPressed(QKeyEvent * event);

private:
    std::function<void (void)> h_;
};
