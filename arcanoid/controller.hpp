#pragma once

#include "stdafx.hpp"
#include "entity.hpp"


class Controller
        : public QObject
        , public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

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
