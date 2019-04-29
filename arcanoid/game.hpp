#pragma once

#include "stdafx.hpp"
#include "entity.hpp"
#include "field.hpp"
#include "timer.hpp"


class Game final
        : private QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);
    ~Game();
    void launch();

private:
    EntityS makePlayer();
    EntityS makeBall();
    std::vector<EntityS> makeBorders(double width = 10);

private:
    constexpr static const QSize DEF_SIZE = { 720, 720 };
    const int64_t FRAME_RATE = 60;

    QGraphicsScene * scene_;
    Timer * timer_;
    FieldP  field_;
    std::vector<EntityS> entities_;
};
