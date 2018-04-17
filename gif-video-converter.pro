QT       += core
TEMPLATE = app
CONFIG += console c++11

LIBS += -lavcodec -lavutil

SOURCES += main.cpp \
    GifLoader.cpp \
    VideoDecoder.cpp

HEADERS += \
    gif.h \
    GifLoader.h \
    VideoDecoder.h
