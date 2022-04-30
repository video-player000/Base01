QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/ffmpeg/include
#LIBS += $$PWD/ffmpeg/lib/avcodec.lib \
#    $$PWD/ffmpeg/lib/avdevice.lib \
#    $$PWD/ffmpeg/lib/avfilter.lib \
#    $$PWD/ffmpeg/lib/avformat.lib \
#    $$PWD/ffmpeg/lib/avutil.lib \
#    $$PWD/ffmpeg/lib/postproc.lib \
#    $$PWD/ffmpeg/lib/swresample.lib \
#    $$PWD/ffmpeg/lib/swscale.lib \
LIBS +=  -L$$PWD/ffmpeg/lib \
         -lavcodec \
         -lavdevice \
         -lavfilter \
        -lavformat \
        -lavutil \
        -lpostproc \
        -lswresample \
        -lswscale

SOURCES += \
    main.cpp \
    videoitem.cpp \
    videoplayer.cpp \
    videoshow.cpp

HEADERS += \
    videoitem.h \
    videoplayer.h \
    videoshow.h

FORMS += \
    videoplayer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    media/222.mp4
