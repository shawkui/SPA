/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the e0amples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY E0PRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, E0EMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
/*
 * This file is created based on the ShapeItems of QT Example: ToolTips
 * Based on the ToolTips example, we added some more data fileds and more powerful shapes to support
 * users' sentific needs;
 */

#include <QtWidgets>

#include "shapeitem.h"

//! [0]
QPainterPath ShapeItem::path() const
{
    return myPath;
}
//! [0]

//! [1]
QPoint ShapeItem::position() const
{
    return myPosition;
}
//! [1]

//! [2]
QColor ShapeItem::color() const
{
    return myColor;
}

//! [2]

//! [3]
QString ShapeItem::toolTip() const
{
    return myToolTip;
}
//! [3]

//! [4]
void ShapeItem::setPath(const QPainterPath &path)
{
    myPath = path;
}
//! [4]

//! [5]
void ShapeItem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}
//! [5]

//! [6]
void ShapeItem::setPosition(const QPoint &position)
{
    myPosition = position;
}
//! [6]

//! [7]
void ShapeItem::setColor(const QColor &color)
{
    myColor = color;
}
//! [7]
//!

/*
 * ---------------------------------
 * The following parts are made by us
 */


void ShapeItem::rotate(double angle)
{
    QPainterPath Path = this->path();
    QTransform transform;
    transform.rotate(angle);
    Path = transform.map(Path);
    this->setPath(Path);

}

void ShapeItem::scale(double c)
{
    QPainterPath Path = this->path();
    QTransform transform;
    transform.scale(c,c);
    Path = transform.map(Path);
    this->setPath(Path);
}

bool ShapeItem::isShow(){
    return show;
}


void ShapeItem::setShow(){
    show=true;
}

void ShapeItem::setPenWidth(int w){
    this->penWidth=w;
}

int ShapeItem::penwidth()const{
    return penWidth;
}

void ShapeItem::drawCurrentSource()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(30, 40);
    Path.addEllipse(QRect(30,20,40,40));
    Path.moveTo(0+70, 40);
    Path.lineTo(100, 40);
    Path.moveTo(34,40);
    Path.lineTo(40,40);
    Path.moveTo(60,40);
    Path.lineTo(66,40);
    Path.moveTo(63,37);
    Path.lineTo(63,43);
    this->setPath(Path);
}

void ShapeItem::drawResistance()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(30, 40);
    Path.addRect(30,35,40,10);
    Path.moveTo(70,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}

void ShapeItem::drawDiode()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(30,40);
    Path.moveTo(0+30, 20);
    Path.lineTo(30,60);
    Path.lineTo(70,40);
    Path.lineTo(30,20);
    Path.moveTo(70,20);
    Path.lineTo(70,60);
    Path.moveTo(70,40);
    Path.lineTo(100,40);
    Path.moveTo(0, 0);
    this->setPath(Path);
}

void ShapeItem::drawCapacity()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(40, 40);
    Path.moveTo(0+40, 20);
    Path.lineTo(40, 60);
    Path.moveTo(0+60, 20);
    Path.lineTo(60, 60);
    Path.moveTo(0+60, 40);
    Path.lineTo(100, 40);

    Path.addEllipse(QRect(40, 80, 20, 20));
    Path.addText(45,95,QFont(), QString("C"));
    Path.moveTo(0+40, 40);
    this->setPath(Path);
}

void ShapeItem::drawGround()
{
    QPainterPath Path;
    Path.moveTo(20,0);
    Path.lineTo(20,30);
    Path.moveTo(0,30);
    Path.lineTo(40, 30);
    Path.moveTo(0+10,40);
    Path.lineTo(30,40);
    Path.moveTo(15,50);
    Path.lineTo(25,50);
    this->setPath(Path);
}


void ShapeItem::drawCopperline(){
    QPainterPath Path;
    Path.addRect(0,39.5,40,1);
    Path.moveTo(0, 40);
    Path.lineTo(40,40);
    this->setPath(Path);
}

void ShapeItem::drawTransistor(){
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(55, 40);
    Path.addEllipse(QRect(30,15,50,50));
    Path.moveTo(55, 15);
    Path.lineTo(55,65);
    Path.moveTo(55, 30);
    Path.lineTo(80,15);
    Path.lineTo(80,0);
    Path.moveTo(55, 50);
    Path.lineTo(80,65);
    Path.lineTo(80,80);
    this->setPath(Path);
}


void ShapeItem::drawInductor(){
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(15, 40);
    Path.lineTo(33-15,36);  //+3,-4
    Path.lineTo(35-15,34.5);  //+2,-1.5
    Path.lineTo(40-15,34.5);    //+5
    Path.lineTo(42-15,36);    //+2,+1.5
    Path.lineTo(45-15,40);    //+3,+4

    Path.lineTo(45-15+3,40-4);  //+3,-4
    Path.lineTo(45-15+3+2,40-5.5);  //+2,-1.5
    Path.lineTo(45-5,40-5.5);    //+5
    Path.lineTo(45-3,40-4);    //+2,+1.5
    Path.lineTo(45,40);    //+3,+4

    Path.lineTo(45+3,40-4);  //+3,-4
    Path.lineTo(45+5,40-5.5);  //+2,-1.5
    Path.lineTo(45+10,40-5.5);    //+5
    Path.lineTo(45+12,40-4);    //+2,+1.5
    Path.lineTo(45+15,40);    //+3,+4

    Path.lineTo(75, 40);

    this->setPath(Path);
}

void ShapeItem::drawAmmeter(){
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(30-15, 40);
    Path.addEllipse(QRect(30-15,15,50,50));
    QFont myfont;
    myfont.setPixelSize(30);
    Path.addText(33,48,myfont, QString("A"));
    Path.moveTo(65, 40);
    Path.lineTo(80,40);
    this->setPath(Path);
}


void ShapeItem::drawVoltmeter(){
    QPainterPath Path;

    Path.moveTo(0, 40);
    Path.lineTo(30-15, 40);
    Path.addEllipse(QRect(30-15,15,50,50));
    Path.moveTo(55-15, 65);
    QFont myfont;
    myfont.setPixelSize(30);
    Path.addText(33,48,myfont, QString("V"));
    Path.moveTo(65, 40);
    Path.lineTo(80,40);

    this->setPath(Path);
}



void ShapeItem::drawBuffer()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(40,40);
    Path.moveTo(0+40, 20);
    Path.lineTo(40,60);
    Path.lineTo(60,40);
    Path.lineTo(40,20);
    Path.moveTo(60,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}

void ShapeItem::drawNotGate()
{
    QPainterPath Path;
    Path.moveTo(0, 40);
    Path.lineTo(40,40);
    Path.moveTo(0+40, 20);
    Path.lineTo(40,60);
    Path.lineTo(60,40);
    Path.lineTo(40,20);
    Path.moveTo(68,40);
    Path.lineTo(100,40);
    Path.addEllipse(QRect(60, 36, 8, 8));
    this->setPath(Path);
}

void ShapeItem::drawAndGate()
{
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(30,30);
    Path.moveTo(0,50);
    Path.lineTo(30,50);
    Path.moveTo(30,20);
    Path.lineTo(30,60);
    Path.moveTo(30,20);
    Path.cubicTo(90,20,90,60,30,60);
    Path.moveTo(75,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}



void ShapeItem::drawNandGate(){
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(30,30);
    Path.moveTo(0,50);
    Path.lineTo(30,50);
    Path.moveTo(30,20);
    Path.lineTo(30,60);
    Path.moveTo(30,20);
    Path.cubicTo(90,20,90,60,30,60);
    Path.addEllipse(75,36.5,7,7);

    Path.moveTo(82,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}
void ShapeItem::drawOrGate()
{
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(38,30);
    Path.moveTo(0,50);
    Path.lineTo(38,50);
    Path.moveTo(30,20);
    Path.quadTo(50,40,30,60);
    Path.quadTo(60,60,75,40);
    Path.quadTo(60,20,30,20);
    Path.moveTo(75,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}

void ShapeItem::drawNorGate()
{
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(38,30);
    Path.moveTo(0,50);
    Path.lineTo(38,50);
    Path.moveTo(30,20);
    Path.quadTo(50,40,30,60);
    Path.quadTo(60,60,75,40);
    Path.quadTo(60,20,30,20);
    Path.addEllipse(75,36.5,7,7);
    Path.moveTo(82,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}

void ShapeItem::drawXORGate()
{
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(38,30);
    Path.moveTo(0,50);
    Path.lineTo(38,50);
    Path.moveTo(30,20);
    Path.quadTo(50,40,30,60);

    Path.quadTo(60,60,75,40);
    Path.quadTo(60,20,30,20);
    Path.moveTo(20,20);
    Path.quadTo(40,40,20,60);
    Path.moveTo(75,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}



void ShapeItem::drawXNORGate()
{
    QPainterPath Path;
    Path.moveTo(0,30);
    Path.lineTo(38,30);
    Path.moveTo(0,50);
    Path.lineTo(38,50);
    Path.moveTo(30,20);
    Path.quadTo(50,40,30,60);

    Path.quadTo(60,60,75,40);
    Path.quadTo(60,20,30,20);
    Path.moveTo(20,20);
    Path.quadTo(40,40,20,60);
    Path.addEllipse(75,36.5,7,7);
    Path.moveTo(82,40);
    Path.lineTo(100,40);
    this->setPath(Path);
}

