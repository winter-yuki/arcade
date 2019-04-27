TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
        main.cpp \
    game.cpp \
    entity.cpp \
    component.cpp \
    field.cpp \
    ecarrowkeys.cpp

HEADERS += \
    stdafx.hpp \
    game.hpp \
    entity.hpp \
    component.hpp \
    field.hpp \
    ecarrowkeys.hpp

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc
