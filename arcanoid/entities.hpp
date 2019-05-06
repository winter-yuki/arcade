#pragma once

#include "engy/entity.hpp"
#include "engy/controllers/eccollisions.hpp"


class Player final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        explicit Player(Engy::Game * game);
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


class Bonus final
        : public Engy::Entity {
    ENGY_CREATABLE_ENTITY

    engy_entity_ctor:
        Bonus(Engy::Game * game, Engy::Entity * ancestor,
              Engy::ECCollisions::Handler applier);

public:
    static void onCollision(Engy::Entity * a, Engy::Entity * b);
};






