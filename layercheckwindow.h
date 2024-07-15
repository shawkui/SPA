/*
 * layerCheckWindow.h
 * This file Design a new widget to show layer state if needed;
 * The widget contains a checkbox to show layer, a botton for active layer and two bottons move layer forward and backward
 * Though it's not used in this prject due to limted time, but it's really useful for a powerful ImageEditor
 */
#ifndef LAYERCHECKWINDOW_H
#define LAYERCHECKWINDOW_H

#include <QWidget>

namespace Ui {
class LayerCheckWindow;
}

class LayerCheckWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCheckWindow(QWidget *parent = 0);
    ~LayerCheckWindow();

private:
    Ui::LayerCheckWindow *ui;
};

#endif // LAYERCHECKWINDOW_H
