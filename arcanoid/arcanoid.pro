include($$PWD/../engy/engy.pri)
INCLUDEPATH += $$PWD/..

TARGET = arcanoid
TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \

HEADERS += \

RESOURCES += \
    arcanoid.qrc
