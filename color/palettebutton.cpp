#include "palettebutton.h"

/* Implementation of the constructor */

PaletteButton::PaletteButton(const QColor & color) {
    paletteColor = color;
    QPixmap pixmap(20, 20);
    pixmap.fill(color);
    setIcon(pixmap);
}

QColor PaletteButton::getColor(){
    return paletteColor;
}
