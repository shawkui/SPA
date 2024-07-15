#ifndef PALETTEBUTTON_H
#define PALETTEBUTTON_H

#include <QToolButton>

/*
 * Class: PaletteButton
 * ---------------------
 * This class defines the buttons which shows and returns the current
 * color of this button
 */

class PaletteButton : public QToolButton {

    Q_OBJECT

public:
    PaletteButton(const QColor & color);
    QColor getColor();

signals:
    void colarPick();


private:
    QColor paletteColor;


};

#endif // PALETTEBUTTON_H
