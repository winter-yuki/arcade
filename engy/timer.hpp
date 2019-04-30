#pragma once

#include "stdafx.hpp"


namespace Engy
{

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

}
