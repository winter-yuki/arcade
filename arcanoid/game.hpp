#pragma once

#include "stdafx.hpp"
#include "entity.hpp"
#include "platform.hpp"


class Game
        : QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);
    void launch();

private:
    constexpr static const QSize DEF_SIZE = { 1280, 720 };

    QGraphicsScene * scene_;
    Platform         * player_;
};
