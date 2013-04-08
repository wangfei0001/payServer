TEMPLATE = app
CONFIG += console
CONFIG -= qt
#CONFIG += debug

SOURCES += main.cpp \
    threadpool.cpp \
    thread.cpp \
    paymentserver.cpp \
    paypal.cpp \
    md5/md5.c \
    data/param.cpp \
    data/authorise.cpp \
    data/response.cpp

HEADERS += \
    threadpool.h \
    thread.h \
    paymentserver.h \
    paypal.h \
    md5/md5_loc.h \
    md5/md5.h \
    md5/conf.h \
    data/param.h \
    data/authorise.h \
    data/response.h

INCLUDEPATH = /usr/include/libxml2

OTHER_FILES += \
    Makefile \
    request.xml

LIBS += \
    -lpthread \
    -lxml2 \
    -lcurl

