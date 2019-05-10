#pragma once

#include "engy/entity.hpp"


class Player final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Player(Engy::Game * game);

public:
    static QGraphicsItem * createForm(QPointF pos, QSizeF size);

    static constexpr char const * NAME = "Player";
};


class Ball final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Ball(Engy::Game * game);

public:
    static constexpr char const * NAME = "Ball";
};


class Block final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        Block(Engy::Game * game, QRectF rect);

public:
    static constexpr char const * NAME = "Block";
};


class MovingBlock final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        MovingBlock(Engy::Game * game, QRectF rect);

public:
    static constexpr char const * NAME = "MovingBlock";
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

    static constexpr char const * NAME = "Bonus";

private:
    Applier applier_;
    QString recepient_ = "Player";
};


class Trampoline final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Trampoline(Engy::Game * game);

public:
    static constexpr char const * NAME = "Trampoline";
};


















