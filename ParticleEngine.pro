#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T15:47:48
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = ParticleEngine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    emitter.cpp \
    particle.cpp \
    camera.cpp \
    glwidget_input.cpp \
    glwidget_slots.cpp \
    texture.cpp \
    resource.cpp \
    glextensions.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    emitter.h \
    particle.h \
    camera.h \
    texture.h \
    resource.h \
    glextensions.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
