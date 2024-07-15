/*
 * Error.h
 * This file make a Error function which will quit the current application and output a string by using qDebug
 */
#ifndef ERROR_H
#define ERROR_H
#include <string>
#include <qdebug.h>
void error(QString msg){
    qDebug()<<msg;
    exit(0);
}

#endif // ERROR_H
