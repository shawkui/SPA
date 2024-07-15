#ifndef PALETTEBAR_H
#define PALETTEBAR_H

#include <QToolBar>
#include "color/customcolor.h"
#include "palettebutton.h"

/*
 * Class: PaletteBar
 * -----------------
 * This class defines to be the container of color buttons
 */

class PaletteBar : public QToolBar {

    Q_OBJECT

public:
    PaletteBar(QToolBar *toolbar);
    void initializePalette();
    QColor getColor();

signals:
     void newColor();


public slots:
    void colorClick(); // update the current color after the click
    void colorClickP(); // update the current color after the click


private:


    CustomColor *customColorButton;
    PaletteButton *colorButton;
    QToolBar *colorBar;
    QColor currentColor;



};


#endif // PALETTEBAR_H
