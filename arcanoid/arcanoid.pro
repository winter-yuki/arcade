include($$PWD/../engy/engy.pri)
INCLUDEPATH += $$PWD/..

TARGET = arcanoid
TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    components.cpp \
    entities.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    components.hpp \
    entities.hpp \
    mainwindow.hpp

RESOURCES += \
    arcanoid.qrc
