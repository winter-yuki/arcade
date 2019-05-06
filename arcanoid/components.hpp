#pragma once

#include "engy/components/value.hpp"
#include "engy/timer.hpp"


class HP final
        : public Engy::ComponentT<HP> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit HP(int hp = 100);

public:
    void changeHp(int dHp = -20);
    int hp() const { return hp_; }

private slots:
    void entityAdded();
    void formChanged();

private:
    const int INITIAL_HP_;
    int hp_;
    QGraphicsTextItem * textItem_ = nullptr;
};


class VMod final
        : public Engy::ComponentT<VMod> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit VMod(float amplitude = 0.01f, int lifeTime = 50000);

public:
    ~VMod() override;

private slots:
    void entitySetted();
    void updateSpeed(int64_t time);
    void updatePos(int64_t dt);
    void vUpdated(QVector2D newV);

private:
    void timerEvent(QTimerEvent * event) override;

private:
    Engy::Timer * timer_ = nullptr;
    QVector2D v0_;
    QVector2D v_;
    float amplitude_;
    int lifeTime_;
};











