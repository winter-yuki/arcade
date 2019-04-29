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
    controllers/field.cpp \
    controllers/ecarrowkeys.cpp \
    controllers/controller.cpp \
    controllers/eccollisions.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    timer.hpp \
    entityptrs.hpp \
    components/component.hpp \
    components/move.hpp \
    controllers/field.hpp \
    controllers/ecarrowkeys.hpp \
    controllers/controller.hpp \
    controllers/eccollisions.hpp \

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc
