TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
        main.cpp \
    game.cpp \
    entity.cpp \
    components/component.cpp \
    components/move.cpp \
    field.cpp \
    ecarrowkeys.cpp \
    timer.cpp \
    controller.cpp \
    eccollisions.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    components/component.hpp \
    components/move.hpp \
    field.hpp \
    ecarrowkeys.hpp \
    timer.hpp \
    controller.hpp \
    eccollisions.hpp \
    entityptrs.hpp

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc
