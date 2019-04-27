#pragma once

#include "stdafx.hpp"


class Timer final
        : public QTimer {
    Q_OBJECT

public:
    explicit Timer(QObject * parent = nullptr);

private slots:
    void timeUpdate();

signals:
    void tick(int64_t dt);

private:
    int64_t prevTime_ = 0;
};
