#include "pencil.h"
#include <QPen>
#include "canva.h"
#include <QPoint>
#include <QPainter>
#include <iostream>
using namespace std;

QPoint penStartPoint;
QPoint penEndPoint;

void penMousePressEvent(QMouseEvent *event, Canva & canva, QPen &currentPen) {
    if (event->button() == Qt::LeftButton) {
        penStartPoint = event->pos();
        penEndPoint = event->pos();
    }
}

void penMouseMoveEvent(QMouseEvent *event, Canva & canva, QPen &currentPen) {
    if(event->buttons()==Qt::LeftButton){
        penEndPoint = event->pos();
        paint(canva, currentPen);
        penStartPoint = event->pos();
    }
}

void penMouseReleaseEvent(QMouseEvent *event, Canva & canva, QPen &currentPen) {
    if (event->button() == Qt::LeftButton) {
        penEndPoint = event->pos();
        paint(canva, currentPen);
    }
}

void paint(Canva & canva, QPen currentPen) {
    QPainter painter(canva.getImage());
    painter.setPen(currentPen);
    if (penStartPoint != penEndPoint) {
        painter.drawLine(penStartPoint, penEndPoint);
        canva.update();
    }
    if (penStartPoint == penEndPoint) {
        painter.drawPoint(penStartPoint);
        canva.update();
    }
}

QPen solidPen(QColor color, int width) {
    QPen solidP;
    solidP.setJoinStyle(Qt::RoundJoin);
    solidP.setCapStyle(Qt::RoundCap);
    solidP.setStyle(Qt::SolidLine);
    solidP.setColor(color);
    solidP.setWidth(width);
    return solidP;
}
QPen dashPen(QColor color, int width) {
    QPen dashP;
    dashP.setJoinStyle(Qt::RoundJoin);
    dashP.setCapStyle(Qt::RoundCap);
    dashP.setStyle(Qt::DashLine);
    dashP.setColor(color);
    dashP.setWidth(width);
    return dashP;
}

QPen dotPen(QColor color, int width) {
    QPen dotP;
    dotP.setJoinStyle(Qt::RoundJoin);
    dotP.setCapStyle(Qt::RoundCap);
    dotP.setStyle(Qt::DotLine);
    dotP.setColor(color);
    dotP.setWidth(width);
    return dotP;
}




