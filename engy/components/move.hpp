/**
  * @file
  */

#pragma once

#include "stdafx.hpp"
#include "component.hpp"
#include "timer.hpp"


namespace Engy
{

/**
 * @ingroup component
 * @brief The Move class
 */
class Move final
        : public Component {
    Q_OBJECT
    ENGY_CREARABLE_COMPONENT

public:
    void setV(QVector2D v); ///< Pixel per second
    QVector2D v() const;

    void timerEvent(QTimerEvent * event) override;

public slots:
    void update(int64_t dt);

private:
    explicit Move(int64_t fps = 60);

private:
    int64_t interval_; ///< In miliseconds
    QVector2D v_ = { 0, 0 };
};

} // Engy










