QT       += core
TEMPLATE = app
CONFIG += console c++14

LIBS += -L/usr/local/lib

LIBS += -lavcodec -lavutil -lavformat
LIBS += -lboost_program_options
LIBS += -lopencv_core -lopencv_imgproc
LIBS += -lswscale

SOURCES += main.cpp \
    GifLoader.cpp \
    VideoDecoder.cpp \
    VideoEncoder.cpp

HEADERS += \
    gif.h \
    GifLoader.h \
    VideoDecoder.h \
    VideoEncoder.h \
    ImageUtils.h
