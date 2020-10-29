TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    actor.cpp \
    city.cpp \
    engine.cpp \
    main.cc \
    passenger.cpp \
    statistics.cpp \
    stop.cpp \
    vehicle.cpp
    ../../CourseLib/graphics/simplemainwindow.cpp

HEADERS += \
    ../../CourseLib/graphics/simplemainwindow.hh \
    actor.hh \
    city.hh \
    engine.hh \
    passenger.hh \
    statistics.hh \
    stop.hh \
    vehicle.hh

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Course/CourseLib/graphics

DEPENDPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Course/CourseLib/graphics

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a
