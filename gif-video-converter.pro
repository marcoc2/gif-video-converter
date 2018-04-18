QT       += core
TEMPLATE = app
CONFIG += console c++14

LIBS += -lavcodec -lavutil

SOURCES += main.cpp \
    GifLoader.cpp \
    VideoDecoder.cpp \
    VideoEncoder.cpp

HEADERS += \
    gif.h \
    GifLoader.h \
    VideoDecoder.h \
    VideoEncoder.h
