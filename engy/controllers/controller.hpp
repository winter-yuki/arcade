#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Controller
        : public QGraphicsObject {
    Q_OBJECT

public:
    Controller(QGraphicsScene * scene, EntityW entity);

    QGraphicsScene * scene();
    EntityW entity();

    // Unused
    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;
    QRectF boundingRect() const override;

public slots:
    void harakiri();

signals:
    void entityDeleted();

private:
    QGraphicsScene * scene_;
    EntityW entity_;
};
