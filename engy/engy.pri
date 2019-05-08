QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/components/basiccollisionhandler.cpp \
    $$PWD/components/collisions.cpp \
    $$PWD/components/mass.cpp \
    $$PWD/controllers/ecscenebounds.cpp \
    $$PWD/game.cpp \
    $$PWD/entity.cpp \
    $$PWD/timer.cpp \
    $$PWD/components/component.cpp \
    $$PWD/components/move.cpp \
    $$PWD/controllers/ecarrowkeys.cpp \
    $$PWD/controllers/controller.cpp

HEADERS += \
    $$PWD/components/basiccollisionhandler.hpp \
    $$PWD/components/collisions.hpp \
    $$PWD/components/intangible.hpp \
    $$PWD/components/mass.hpp \
    $$PWD/components/value.hpp \
    $$PWD/controllers/ecscenebounds.hpp \
    $$PWD/defs.hpp \
    $$PWD/stdafx.hpp \
    $$PWD/game.hpp \
    $$PWD/entity.hpp \
    $$PWD/timer.hpp \
    $$PWD/components/component.hpp \
    $$PWD/components/move.hpp \
    $$PWD/controllers/ecarrowkeys.hpp \
    $$PWD/controllers/controller.hpp

PRECOMPILED_HEADER = $$PWD/stdafx.hpp

INCLUDEPATH += $$PWD
