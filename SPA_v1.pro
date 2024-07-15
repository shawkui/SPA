#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T22:19:07
#
#-------------------------------------------------

# include JKQTmathText source-code, including the open-source XITS fonts
include(../SPA_vi/ MathText/jkqtmathtext_with_xits.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SPA_v1
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    canva.cpp \
    shapeitem.cpp \
    imageitem.cpp \
    mainwindow2.cpp \
    funcwindow.cpp \
    qcustomplot.cpp \
    basiclasso.cpp \
    MathText/jkqtmathtext.cpp \
    MathText/jkqtptools.cpp \
    textinput.cpp \
    colorFilter/abstractfilter.cpp \
    colorFilter/grayfilter.cpp \
    colorFilter/negativefilter.cpp \
    color/palettebar.cpp \
    color/palettebutton.cpp \
    layercheckwindow.cpp \
    pencil/pencil.cpp \
    color/customcolor.cpp

HEADERS += \
        mainwindow.h \
    canva.h \
    shapeitem.h \
    imageitem.h \
    mainwindow2.h \
    funcwindow.h \
    qcustomplot.h \
    basiclasso.h \
    error.h \
    shapetype.h \
    MathText/jkqtmathtext.h \
    MathText/jkqtp_imexport.h \
    MathText/jkqtptools.h \
    textinput.h \
    colorFilter/abstractfilter.h \
    colorFilter/grayfilter.h \
    colorFilter/negativefilter.h \
    color/palettebar.h \
    color/palettebutton.h \
    layercheckwindow.h \
    pencil/pencil.h \
    color/customcolor.h

FORMS += \
        mainwindow.ui \
    funcwindow.ui \
    textinput.ui \
    layercheckwindow.ui

DISTFILES += \
    MathText/jkqtmathtext.pri \
    MathText/jkqtmathtext_with_xits.pri \
    MathText/math_fonts/xits.pri

RESOURCES += \
    MathText/math_fonts/xits.qrc
