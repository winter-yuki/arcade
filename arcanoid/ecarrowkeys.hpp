#pragma once

#include "entity.hpp"


class ECArrowKeys final
        : public QGraphicsItem {
public:
    ECArrowKeys(QGraphicsScene * scene, EntityP entity);

    void setDx(double dx);
    double dx() const;

    void setRBorder(double rborder);
    double rborder() const;
    void setLBorder(double lborder);
    double lborder() const;


    void keyPressEvent(QKeyEvent * event) override;

    void paint(QPainter * painter, QStyleOptionGraphicsItem const * option,
               QWidget * widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    QGraphicsScene * scene_;
    EntityP entity_;
    double dx_ = 20;

    double lborder_ = 0;
    double rborder_ = 0;
};
