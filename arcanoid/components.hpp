#pragma once

#include "engy/components/value.hpp"
#include "engy/timer.hpp"
#include "engy/components/collisions.hpp"
#include "engy/components/basiccollisionhandler.hpp"


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


class PlatformSize final
        : public Engy::ComponentT<PlatformSize> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        PlatformSize(qreal c, int hits = 3);

public:
    ~PlatformSize();

    static void counter(Engy::Entity * a, Engy::Entity * b);

private:
    qreal coef_;
    int hitsLeft_;
};


class Shimmer final
        : public Engy::ComponentT<Shimmer> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit Shimmer(int period = 5000);

public:
    ~Shimmer() override;

private:
    void timerEvent(QTimerEvent * event) override;
    QGraphicsItem * item_ = nullptr;
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












