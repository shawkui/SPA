/*
 * textInput.h
 * This file design a widget inherit from QWidget to show a window for users' text input
 * The underlying text complier is from Jan W. Krieger (<jan@jkrieger.de>, <j.krieger@dkfz.de>), German Cancer Research Center (DKFZ) & IWR, University of Heidelberg
 * This window can accept both latex input and nomal text input
 * The default $$ is not necessary to compile math text
 * For more information, please refer to the readme.md in folder MathText, which is written by j.krieger
 *
 */
#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class textInput;
}

class textInput : public QDialog
{
    Q_OBJECT

public:
    explicit textInput(QWidget *parent);
    ~textInput();
    QPixmap getEquation();
signals:
    addEquation();

private slots:
    /*
     * private slots gengerated from QDesigner
     */
    void on_commandLinkButton_clicked();

    void on_buttonBox_accepted();

    void on_color_clicked();

private:
    Ui::textInput *ui;
    QPixmap pix; /* text image */
    QColor fontCOlor; /* font color */
};

#endif // TEXTINPUT_H
