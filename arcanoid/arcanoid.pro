TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    game.cpp \
    entity.cpp \
    timer.cpp \
    components/component.cpp \
    components/move.cpp \
    components/mass.cpp \
    controllers/field.cpp \
    controllers/ecarrowkeys.cpp \
    controllers/controller.cpp \
    controllers/eccollisions.cpp \
    controllers/collision_handlers.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    timer.hpp \
    entityptrs.hpp \
    components/component.hpp \
    components/move.hpp \
    components/mass.hpp \
    controllers/field.hpp \
    controllers/ecarrowkeys.hpp \
    controllers/controller.hpp \
    controllers/eccollisions.hpp \
    controllers/collision_handlers.hpp

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc
