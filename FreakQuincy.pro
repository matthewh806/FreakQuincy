######################################################################
# Automatically generated by qmake (3.1) Fri Feb 22 13:40:07 2019
######################################################################

QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TEMPLATE = app
TARGET = FreakQuincy
INCLUDEPATH += .
INCLUDEPATH += /usr/include 
INCLUDEPATH += /usr/local/include
INCLUDEPATH += include/
LIBS += -L/usr/lib -L/usr/local/lib -lstdc++ -lfftw3 -lm -pthread
LIBS += -framework CoreFoundation -framework CoreAudio -framework CoreMIDI

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -g
    DESTDIR = bin/debug
    BUILDIR = build/debug
} else {
    DESTDIR = bin/release
    BUILDIR = build/release
}

OBJECTS_DIR = $$BUILDIR/.OBJECTS_DIR
MOC_DIR = $$BUILDIR/.MOC_DIR
RCC_DIR = $$BUILDIR/.qrc
UI_DIR = $$BUILDIR/.u

DEFINES += __MACOSX_CORE__

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += include/dep/*.h
HEADERS += include/engine/*.hpp
HEADERS += include/ui/*.hpp
SOURCES  += src/dep/*.cpp
SOURCES += src/*.cpp
SOURCES += src/engine/*.cpp
SOURCES += src/ui/*.cpp