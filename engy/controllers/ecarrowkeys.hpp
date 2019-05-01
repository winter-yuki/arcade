#pragma once

#include "controller.hpp"


namespace Engy
{

class ECArrowKeys final
        : public Controller {
    Q_OBJECT

public:
    using OptD = std::optional<double>;

    ECArrowKeys(Game * game, EntityW entity);

    void setDx(OptD dx);
    OptD dx() const;
    void setDy(OptD dy);
    OptD dy() const;

    void setRBorder(OptD x);
    OptD rborder() const;
    void setLBorder(OptD x);
    OptD lborder() const;
    void setTBorder(OptD x);
    OptD tborder() const;
    void setBBorder(OptD x);
    OptD bborder() const;

    void keyPressEvent(QKeyEvent * event) override;

private:
    std::optional<QPointF> left (EntityS & e) const;
    std::optional<QPointF> right(EntityS & e) const;
    std::optional<QPointF> up   (EntityS & e) const;
    std::optional<QPointF> down (EntityS & e) const;

private:
    OptD dx_ = 20;
    OptD dy_ = 20;

    OptD lborder_ = std::nullopt;
    OptD rborder_ = std::nullopt;
    OptD tborder_ = std::nullopt;
    OptD bborder_ = std::nullopt;
};

} // Engy
