/**
  * @file
  */

#pragma once

#include "stdafx.hpp"


namespace Engy
{

/**
 * @ingroup core
 * @brief The Timer class
 */
class Timer final
        : public QTimer {
    Q_OBJECT

public:
    explicit Timer(QObject * parent = nullptr);

    int64_t time() const;

private slots:
    void timeUpdate();

signals:
    void tickdt  (int64_t dt);
    void tickTime(int64_t time);

private:
    int64_t time_ = 0;
};

} // Engy
