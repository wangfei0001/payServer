TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    threadpool.cpp \
    thread.cpp \
    paymentserver.cpp

HEADERS += \
    threadpool.h \
    thread.h \
    paymentserver.h

OTHER_FILES += \
    Makefile

LIBS += \
    -lpthread \
    -lcurl

