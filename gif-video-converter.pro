QT       += core
TEMPLATE = app
CONFIG += console c++14

LIBS += -lavcodec -lavutil -lavformat
LIBS += -lboost_program_options

SOURCES += main.cpp \
    GifLoader.cpp \
    VideoDecoder.cpp \
    VideoEncoder.cpp

HEADERS += \
    gif.h \
    GifLoader.h \
    VideoDecoder.h \
    VideoEncoder.h
