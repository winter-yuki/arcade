#pragma once

#include "controller.hpp"


class ECArrowKeys final
        : public Controller {
public:
    ECArrowKeys(QGraphicsScene * scene, EntityP entity);

    void setDx(double dx);
    double dx() const;

    void setRBorder(double rborder);
    double rborder() const;
    void setLBorder(double lborder);
    double lborder() const;

    void keyPressEvent(QKeyEvent * event) override;

private:
    double dx_ = 20;
    double lborder_ = 0;
    double rborder_ = 0;
};
