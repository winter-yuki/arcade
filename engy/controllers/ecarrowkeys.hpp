#pragma once

#include "controller.hpp"


namespace Engy
{

class ECArrowKeys final
        : public Controller {
    Q_OBJECT

public:
    ECArrowKeys(QGraphicsScene * scene, EntityW entity);

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

} // Engy
