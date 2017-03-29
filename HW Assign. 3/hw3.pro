TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/Cellar/armadillo/6.400.3_1/include

SOURCES += main.cpp

LIBS += -llapack -lblas
