TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
        main.cpp \
    game.cpp \
    entity.cpp \
    component.cpp \
    render.cpp \
    player.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    component.hpp \
    render.hpp \
    player.hpp

PRECOMPILED_HEADER = stdafx.hpp
