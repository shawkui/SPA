#include "palettebar.h"
#include "color/customcolor.h"
#include <QDebug>
class CustomColor;

/* Implementation of the constructor */

PaletteBar::PaletteBar(QToolBar *toolbar) : QToolBar("Colors") {

    currentColor=Qt::transparent;
    colorBar = toolbar;
    initializePalette();
}


/* Implementation: initialzePalette
 * --------------------------------
 * This method initializes the palette which contains three
 * custom self-defined color buttons and the fixed color buttons
 */

void PaletteBar:: initializePalette() {
    customColorButton = new CustomColor(254, 67, 101, this);
    connect(customColorButton, SIGNAL(clicked(bool)), customColorButton, SLOT(selectColor()));
    connect(customColorButton, SIGNAL(finshedColor()), this, SLOT(colorClickP()));
    addWidget(customColorButton);

    customColorButton = new CustomColor(249, 205, 173, this);
    connect(customColorButton, SIGNAL(clicked(bool)), customColorButton, SLOT(selectColor()));
    connect(customColorButton, SIGNAL(finshedColor()), this, SLOT(colorClickP()));
    addWidget(customColorButton);

    customColorButton = new CustomColor(131, 175, 155, this);
    connect(customColorButton, SIGNAL(clicked(bool)), customColorButton, SLOT(selectColor()));
    connect(customColorButton, SIGNAL(finshedColor()), this, SLOT(colorClickP()));
    addWidget(customColorButton);

    colorButton = new PaletteButton(Qt::black);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::white);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::red);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::yellow);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::green);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::cyan);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    addWidget(colorButton);

    colorButton = new PaletteButton(Qt::blue);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(colorClick()));
    //colorButton->clicked();
    addWidget(colorButton);
}

void PaletteBar::colorClick() {
    PaletteButton *currentButton= static_cast<PaletteButton*>(sender());
    currentColor=currentButton->getColor();

    emit newColor();

}

void PaletteBar::colorClickP() {
    CustomColor *currentButton= static_cast<CustomColor*>(sender());
    currentColor=currentButton->getColor();
    emit newColor();

}

QColor PaletteBar::getColor(){
    return currentColor;
}
