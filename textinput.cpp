/*
 * textInput.cpp
 * This file implement a widget inherit from QWidget to show a window for users' text input
 * The underlying text complier is from Jan W. Krieger (<jan@jkrieger.de>, <j.krieger@dkfz.de>), German Cancer Research Center (DKFZ) & IWR, University of Heidelberg
 * This window can accept both latex input and nomal text input
 * The default $$ is not necessary to compile math text
 * For more information, please refer to the readme.md in folder MathText, which is written by j.krieger
 *
 */
#include "textinput.h"
#include "ui_textinput.h"
#include "MathText/jkqtmathtext.h"
#include <QColorDialog>

#include <QDebug>

textInput::textInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textInput)
{
    ui->setupUi(this);

    fontCOlor=Qt::black;
    setWindowTitle(tr("Latex Equation"));
    ui->ImageSizeBoxH->setRange(100,1000);
    ui->ImageSizeBoxH->setValue(100);
    ui->ImageSizeBoxW->setRange(100,1000);
    ui->ImageSizeBoxW->setValue(200);
    ui->FontSizeBox->setRange(5,100);
    ui->FontSizeBox->setValue(20);
    QPixmap icon=QPixmap(20,20);
    icon.fill(fontCOlor);
    ui->color->setIcon(icon);
    ui->color->setIconSize(QSize(20,20));

}

textInput::~textInput()
{
    delete ui;
}

void textInput::on_commandLinkButton_clicked()
{
    QString input=ui->InputText->toPlainText();
    int height=ui->ImageSizeBoxH->text().toInt();
    int width=ui->ImageSizeBoxW->text().toInt();
    int fontSize=ui->FontSizeBox->text().toInt();
    pix=QPixmap(height,width);
    pix.fill(Qt::transparent); //by fefault, the background color is designed as transparent
    qDebug()<<width<<height<<fontSize;
    QPainter painter;

    JKQTmathText mathText;
    mathText.useXITS();
    mathText.set_fontSize(fontSize);
    mathText.set_fontColor(fontCOlor);
    mathText.parse(input);
    painter.begin(&pix);
    mathText.draw(painter, Qt::AlignCenter, QRectF(0,0,pix.width(), pix.height()), false);
    painter.end();
    ui->scrollArea->setAlignment(Qt::AlignCenter);
    ui->EquationArea->setAlignment(Qt::AlignCenter);
    ui->EquationArea->setPixmap(pix);
    ui->EquationArea->resize(height,width);

}

void textInput::on_buttonBox_accepted()
{
    pix.save("latexEquation.png");
    emit addEquation();

}

QPixmap textInput::getEquation(){
    return pix;
}

void textInput::on_color_clicked()
{

    QColor color=QColorDialog::getColor(fontCOlor,this);
    fontCOlor=color;
    QPixmap icon=QPixmap(20,20);
    icon.fill(fontCOlor);
    ui->color->setIcon(icon);
    ui->color->setIconSize(QSize(20,20));
}
