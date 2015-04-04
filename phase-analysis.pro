#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T22:30:50
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

macx {
  QMAKE_CXXFLAGS += -stdlib=libc++
  LIBS += -stdlib=libc++
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phase-analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    phasegraph.cpp \
    graph.cpp \
    changesgraph.cpp \
    phasegraphwidget.cpp

HEADERS  += mainwindow.h \
    phasegraph.h \
    graph.h \
    changesgraph.h \
    phasegraphwidget.h

FORMS    += mainwindow.ui \
    phasegraphwidget.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
