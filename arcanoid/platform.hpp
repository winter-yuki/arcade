#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Platform final
        : public QGraphicsPixmapItem
        , public Entity {
public:
    explicit Platform(QGraphicsPixmapItem * parent = nullptr);

    void keyPressEvent(QKeyEvent * event) override;
};
