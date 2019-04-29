#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T01:47:40
#
#-------------------------------------------------

QT += core gui widgets

TARGET = engy
TEMPLATE = lib
CONFIG += staticlib c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
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
    timer.hpp \
    entity.hpp \
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
