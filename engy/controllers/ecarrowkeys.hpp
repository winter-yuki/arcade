/**
  * @file
  */

#pragma once

#include "controller.hpp"


namespace Engy
{

/**
 * @ingroup controllers
 * @brief The ECArrowKeys class
 * Controller that handles arrow keys events.
 */
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

private slots:
    void sceneResized();

private:
    QPointF left (EntityS & e) const;
    QPointF right(EntityS & e) const;
    QPointF up   (EntityS & e) const;
    QPointF down (EntityS & e) const;

private:
    OptD dx_ = 20;
    OptD dy_ = 20;

    OptD lborder_ = std::nullopt;
    OptD rborder_ = std::nullopt;
    OptD tborder_ = std::nullopt;
    OptD bborder_ = std::nullopt;
};

} // Engy
