#ifndef CUSTOMCOLOR_H
#define CUSTOMCOLOR_H

#include <QToolButton>
#include <QColorDialog>
#include <QPainter>
#include <QColor>
#include <QPixmap>

/*
 * Class: CustomColor
 * ------------------
 * This class defines the buttons which shows, updates and returns the current
 * color of the custom self-defined color button
 */

class CustomColor : public QToolButton {

    Q_OBJECT

public:
    CustomColor(const int & r, const int & g, const int & b, QWidget *parent = 0);

    ~CustomColor();
    QColor getColor();
signals:
   void finshedColor();

private:
    QColor *currentColor;
    QPixmap *pixmap;
    QPainter *paintColor;

public slots:
    void selectColor();


};


#endif // CUSTOMCOLOR_H
