TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    game.cpp \

HEADERS += \
    stdafx.hpp \
    game.hpp \

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    arcanoid.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../engy/release/ -lengy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../engy/debug/ -lengy
else:unix: LIBS += -L$$OUT_PWD/../engy/ -lengy

INCLUDEPATH += $$PWD/../engy
DEPENDPATH += $$PWD/../engy

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engy/release/libengy.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engy/debug/libengy.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engy/release/engy.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../engy/debug/engy.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../engy/libengy.a
