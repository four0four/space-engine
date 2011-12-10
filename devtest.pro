#-------------------------------------------------
#
# Project created by QtCreator 2011-10-11T16:30:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = devtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fileIO.cpp \
    renderer.cpp \
    sprite.cpp \
    shaders.cpp

HEADERS += \
    fileIO.h \
    renderer.h \
    sprite.h \
    shaders.h

OTHER_FILES += \
    vertexshader.vert \
    fragmentshader.frag \
    resources/vertexshader.vert \
    resources/fragmentshader.frag

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
INCLUDEPATH += $$PWD/../../../../usr/include/libxml2
DEPENDPATH += $$PWD/../../../../usr/include/libxml2

#unix:!macx:!symbian: LIBS += -lsfml-graphics

#unix:!macx:!symbian: LIBS += -lsfml-window

unix:!macx:!symbian: LIBS += -lfreeimage
unix:!macx:!symbian: LIBS += /usr/lib/libGL.so
unix:!macx:!symbian: LIBS += /usr/lib/libSDL.so
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glew






#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lxml2
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lxml2
#else:symbian: LIBS += -lxml2
#else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lxml2

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/release/xml2.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/debug/xml2.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/libxml2.a

