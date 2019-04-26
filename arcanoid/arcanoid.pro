TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
        main.cpp \
    game.cpp \
    entity.cpp \
    component.cpp \
    platform.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    component.hpp \
    platform.hpp \
    border.hpp

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc
