#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Controller
        : public QObject
        , public QGraphicsItem {
public:
    Controller(QGraphicsScene * scene, EntityP entity);

    QGraphicsScene * scene();
    EntityP entity();

    // Unused
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    QGraphicsScene * scene_;
    EntityP entity_;
};
