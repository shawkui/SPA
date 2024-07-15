#ifndef PENCIL_H
#define PENCIL_H

#include <QPen>
#include <QMouseEvent>
#include "canva.h"
#include <QPoint>

void penMousePressEvent(QMouseEvent *event, Canva & canva, QPen &currentPen);
void penMouseMoveEvent(QMouseEvent *event, Canva & canva, QPen &currentPen);
void penMouseReleaseEvent(QMouseEvent *event, Canva & canva, QPen &currentPen);


QPen solidPen(QColor color = Qt::black, int width = 10);
QPen dashPen(QColor color = Qt::black, int width = 10);
QPen dotPen(QColor color = Qt::black, int width = 10);

void paint(Canva & canva, QPen currentPen);





#endif // PENCIL_H
