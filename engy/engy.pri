QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/game.cpp \
    $$PWD/entity.cpp \
    $$PWD/timer.cpp \
    $$PWD/components/component.cpp \
    $$PWD/components/move.cpp \
    $$PWD/components/mass.cpp \
    $$PWD/controllers/field.cpp \
    $$PWD/controllers/ecarrowkeys.cpp \
    $$PWD/controllers/controller.cpp \
    $$PWD/controllers/eccollisions.cpp \
    $$PWD/controllers/collision_handlers.cpp

HEADERS += \
    $$PWD/stdafx.hpp \
    $$PWD/game.hpp \
    $$PWD/entity.hpp \
    $$PWD/timer.hpp \
    $$PWD/components/component.hpp \
    $$PWD/components/move.hpp \
    $$PWD/components/mass.hpp \
    $$PWD/controllers/field.hpp \
    $$PWD/controllers/ecarrowkeys.hpp \
    $$PWD/controllers/controller.hpp \
    $$PWD/controllers/eccollisions.hpp \
    $$PWD/controllers/collision_handlers.hpp \
    $$PWD/entityptrs.hpp

PRECOMPILED_HEADER = $$PWD/stdafx.hpp

INCLUDEPATH += $$PWD
