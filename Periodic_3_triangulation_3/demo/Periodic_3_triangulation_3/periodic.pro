######################################################################
# Automatically generated by qmake (2.01a) Fri Jan 25 17:43:03 2008
######################################################################

TEMPLATE = app
TARGET = periodic
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += cgal.h periodic.h Scene.h
FORMS += periodic.ui
SOURCES += main.cpp \
           periodic.cpp \
           Scene.cpp

QMAKE_MAKEFILE=Makefile.periodic
LIBS+=-lCGAL -lQGLViewer

QT += xml opengl script