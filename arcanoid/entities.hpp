#pragma once

#include "engy/entity.hpp"


class Player final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Player(Engy::Game * game);

public:
    void changeSize(int coef);
};


class Ball final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Ball(Engy::Game * game);
};


class Box final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        Box(Engy::Game * game, QRectF rect);
};

class GameWidget;

class Bonus final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        Bonus(Engy::Game * game, Engy::Entity * ancestor);

public:
    using Applier = std::function<void (Engy::Entity *)>;
    void setApplier(Applier a);
    void setRecepient(QString name);

private:
    Applier applier_;
    QString recepient_ = "Player";
};


class Trampoline final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Trampoline(Engy::Game * game);
};


















