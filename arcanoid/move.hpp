#pragma once

#include "stdafx.hpp"
#include "component.hpp"
#include "timer.hpp"


class Move final
        : public QObject
        , public Component {
    Q_OBJECT

public:
    explicit Move(Entity * owner, Timer * timer);
    ~Move();

    void setV(QVector2D v); // Pixel per second
    QVector2D v() const;

public slots:
    void update(int64_t dt);

private:
    Timer * timer_;
    QVector2D v_;
};












