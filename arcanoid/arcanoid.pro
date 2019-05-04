include($$PWD/../engy/engy.pri)
INCLUDEPATH += $$PWD/..

TARGET = arcanoid
TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    entities.cpp \
    main.cpp \

HEADERS += \ \
    entities.hpp

RESOURCES += \
    arcanoid.qrc
