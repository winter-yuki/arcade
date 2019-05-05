#pragma once

#include "engy/components/value.hpp"


class HP final
        : public Engy::ComponentT<HP> {
    ENGY_CREATABLE_COMPONENT

    engy_component_ctor:
        explicit HP(int hp = 100);

public:
    void changeHp(int dHp = -20);
    int hp() const { return hp_; }

    static void hpCounter(Engy::Entity * a, Engy::Entity * b);

private slots:
    void entityAdded();
    void formChanged();

private:
    const int INITIAL_HP_;
    int hp_;
    QGraphicsTextItem * textItem_ = nullptr;
};
