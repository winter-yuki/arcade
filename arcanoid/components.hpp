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


class GameWidget;

class ScoreCounter final
        : public Engy::CollisionHandlerT<ScoreCounter> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit ScoreCounter(GameWidget * gw);

public:
    Engy::Collisions::Handler handler() const override;

private:
    GameWidget * gw_;
};


class HpCounter final
        : public Engy::CollisionHandlerT<HpCounter> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        HpCounter() = default;

public:
    Engy::Collisions::Handler handler() const override;
};


//class BonusCreator final
//        : public Engy::CollisionHandlerT<BonusCreator> {
//    ENGY_CREATABLE_COMPONENT

//    engy_component_ctor:
//        BonusCreator() = default;

//public:
//    Engy::Collisions::Handler handler() const override;

//    Bonus::Applier getRandomBonus();
//};













