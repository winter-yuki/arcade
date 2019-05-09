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
        : public ComponentT<Move> {
    Q_OBJECT
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit Move(int updateInterval = UPDATE_INTERVAL);

public:
    void setV(QVector2D v); ///< Pixel per second
    QVector2D v() const;
    /**
     * @brief setBlock
     * @param b true disables entity movement, false restores.
     */
    void setBlock(bool b);

    void timerEvent(QTimerEvent * event) override;

public slots:
    void update(int64_t dt);

signals:
    void vChanged(QVector2D newV);

private:
    int64_t interval_; ///< In miliseconds
    QVector2D v_ = { 0, 0 };
    bool block_ = false;
};

} // Engy










