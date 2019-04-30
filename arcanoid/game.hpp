#pragma once

#include "stdafx.hpp"
#include "engy/entity.hpp"
#include "engy/timer.hpp"
#include "engy/controllers/field.hpp"


class Game final
        : private QGraphicsView {
public:
    explicit Game(QWidget * parent = nullptr);
    ~Game();
    void launch();

private:
    Engy::EntityS makePlayer();
    Engy::EntityS makeBall();
    std::vector<Engy::EntityS> makeBorders(double width = 10);

private:
    constexpr static const QSize DEF_SIZE = { 720, 720 };
    const int64_t FRAME_RATE = 60;

    QGraphicsScene * scene_;
    Engy::Timer * timer_;
    Engy::FieldP  field_;
    std::vector<Engy::EntityS> entities_;
};
