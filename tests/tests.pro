TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    testthreadpool.cpp

HEADERS += \
    testthreadpool.h

LIBS += \
    -lcppunit

