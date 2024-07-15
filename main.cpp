/*
 * main.cpp
 * This file open and run a new application SAP
 */
#include "mainwindow.h"
#include <QApplication>
#include "textinput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(500,500);
    w.show();


    return a.exec();
}
