#include "customcolor.h"
#include <QColor>
#include <QColorDialog>
#include <QPainter>
#include <QPixmap>

/* Implementation of constructor */

CustomColor::CustomColor(const int & r, const int & g, const int & b,
                         QWidget *parent) : QToolButton(parent) {

    currentColor = new QColor(r, g, b);
    pixmap = new QPixmap(25, 25);
    pixmap->fill(*currentColor);
    setIcon(*pixmap);


}

CustomColor::~CustomColor() {
    delete currentColor;
}


/* Implementation: selectColor
 * ---------------------------
 * This method allows the client to choose the color and the icon
 * will be updated with the chosen color
 */

void CustomColor::selectColor() {
    QColor color = QColorDialog::getColor(*currentColor,this);
    *currentColor = color;
    pixmap->fill(*currentColor);
    setIcon(*pixmap);
    emit finshedColor();

}

QColor CustomColor::getColor(){
    return *currentColor;
}
