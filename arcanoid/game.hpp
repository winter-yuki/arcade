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
    EntityP makeBall();
    std::vector<EntityP> makeBorders(double width = 10);

private:
    constexpr static const QSize DEF_SIZE = { 720, 720 };

    QGraphicsScene * scene_;
    std::vector<EntityP> entities_;
};
