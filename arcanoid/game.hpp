#pragma once

#include "stdafx.hpp"

#include "entity.hpp"


class Game
        : QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);

    void setWinSize(QSize size);
    void launch();

//    void keyPressEvent(QKeyEvent * event) override; TODO

private:
    constexpr static const QSize DEF_SIZE = { 1280, 720 };

    QGraphicsScene * scene_;
};
