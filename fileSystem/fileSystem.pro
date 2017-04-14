#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T13:06:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filewin.cpp \
    inputdialog.cpp \
    directory.cpp \
    filesys.cpp \
    file.cpp \
    openedfile.cpp \
    text.cpp \
    errormess.cpp

HEADERS  += mainwindow.h \
    filewin.h \
    inputdialog.h \
    directory.h \
    filesys.h \
    main.h \
    file.h \
    openedfile.h \
    text.h \
    errormess.h

FORMS    += mainwindow.ui \
    filewin.ui \
    inputdialog.ui \
    text.ui \
    errormess.ui

RESOURCES += \
    pic.qrc
