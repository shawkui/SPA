/*
 * layerCheckWindow.h
 * This file Design a new widget to show layer state if needed;
 * The widget contains a checkbox to show layer, a botton for active layer and two bottons move layer forward and backward
 * Though it's not used in this prject due to limted time, but it's really useful for a powerful ImageEditor
 */
#include "layercheckwindow.h"
#include "ui_layercheckwindow.h"

LayerCheckWindow::LayerCheckWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCheckWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(true);
    ui->pushButton->setCheckable(true);
    ui->pushButton->setChecked(true);


}

LayerCheckWindow::~LayerCheckWindow()
{
    delete ui;
}
