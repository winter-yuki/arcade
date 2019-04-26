#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Platform final
        : public QGraphicsPixmapItem
        , public Entity {
public:
    explicit Platform(QGraphicsPixmapItem * parent = nullptr);

    void keyPressEvent(QKeyEvent * event) override;

    void setDx(size_t dx) { dx_ = dx;   }
    size_t  dx() const    { return dx_; }

private:
    size_t dx_ = 20;
};
