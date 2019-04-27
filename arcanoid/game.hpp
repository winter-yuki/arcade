#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Game
        : private QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);
    void launch();

private:
    EntityP makePlayer();
    std::vector<EntityP> makeBorders();

private:
    constexpr static const QSize DEF_SIZE = { 1280, 720 };

    QGraphicsScene * scene_;
    std::vector<EntityP> entities_;
};
