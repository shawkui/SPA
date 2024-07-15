#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "canva.h"

#include <QAction>
#include <qpushbutton.h>
#include <mainwindow2.h>
#include "funcwindow.h"
#include "color/palettebar.h"
#include "textinput.h"
#include "layercheckwindow.h"
#include "funcwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void passIndex(int index);

private:
    FuncWindow* func;    /* function window for math plot */
    Ui::MainWindow *ui; /* ui file, the mainwindow itself */
    QPushButton *button;
        MainWindow2 w2; /*mainwindow2: the screenshoot window */
    Canva *MyCanva;     /* the central widget of SPA to show and edit images */
    QAction *openAct,*loadAct, *saveAct,*saveAsAct, *rotationCloAct,  /* Menubar bar acctions */
    *rotationCunCloAct, *zoomInAct, *zoomOutAct,*screenshotAct,*filterAct,
    *gridAct,*saveWithGridActt,*creationAct,*grayfilterAct, *negativefilterAct;
    QList<QAction*> *layersAction, *layerActive; /* menubar dynamic actions for show/active layers */
    QMenu *layerMenu,*layerActiveMenu; /* layer menu */
    QToolBar *toolBar; /* toolbar */
    PaletteBar *paletteBar; /* the righthand side color palettebar */
    textInput *textWindow; /* text input window */



private slots:
    /*
     * private slots for mainwindow to connect with its actions, buttons and so on.
     * most of them are generated from QDesigner
     * due to the limitation of time, some of the buttons' names are not meaningful but just the index in the window;
     * Thus, for more details, please refer to Qdesigner for more information;
     */
    void loadPlotFromFile();
    void openAction();
    void loadAction();
    void saveAction();
    void saveAsAction();
    void rotationCloAction();
    void rotationCunCloAction();
    void zoomInAction();
    void zoomOutAction();
    void screenshotAction();
    void filterAction();
    void gridAction();
    void saveWithGridAction();
    void getMewColor();
    void createLayer();
    void createActlayer();
    void showLayer();
    void activeLayer();
    void showMainWindow2();
    void showFuncWindow();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_checkBox_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_22_clicked();
    void loadEquation();
    void grayfilterAction();
    void negativefitlerAction();
    void on_pushButton_28_clicked();
    void on_checkBox_2_clicked();
    void on_Color_clicked();
    void trunToEditShape();
    void trunToEditImage();
    void on_ShapeZoomin_clicked();
    void on_ShapeZoomOut_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_29_clicked();
    void on_spinBox_valueChanged();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_NormalButton_clicked();
    void on_SelectionButton_clicked();
    void on_Pen_clicked();
    void on_Wire_clicked();
    void on_lass_clicked();
    void on_slod_clicked();
    void on_dash_clicked();
    void on_dot_clicked();
};

#endif // MAINWINDOW_H
