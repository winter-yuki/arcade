include($$PWD/../engy/engy.pri)
INCLUDEPATH += $$PWD/..

TARGET = arcanoid
TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    components.cpp \
    controllers.cpp \
    entities.cpp \
    gamewidget.cpp \
    main.cpp

HEADERS += \
    components.hpp \
    controllers.hpp \
    entities.hpp \
    gamewidget.hpp

RESOURCES += \
    arcanoid.qrc
