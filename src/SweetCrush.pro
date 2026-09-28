TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT -= gui

SOURCES += main.cpp \
    bits.cpp \
    tablero.cpp \
    juego.cpp

HEADERS += bits.h \
    tablero.h \
    juego.h
