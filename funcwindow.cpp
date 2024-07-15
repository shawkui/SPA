#include "funcwindow.h"
#include "ui_funcwindow.h"
#include <iostream>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QApplication>
#include <QMetaEnum>

FuncWindow::FuncWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FuncWindow)
{
    ui->setupUi(this);
    ui->lineEdit->text();
    setGeometry(400, 250, 542, 390);
}

FuncWindow::~FuncWindow()
{
    delete ui;
}


void FuncWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
  // generate some data:
  QVector<double> x(10000*this->range+1), y(10000*this->range+1); // initialize with entries 0..10000*range
  for (int i=0; i<10000*this->range+1; ++i)
  {
    x[i] = 1.0*i/5000 - this->range; // x goes from -range to range
    y[i] = this->a*(x[i]-this->b)*(x[i]-this->b)+this->c;  // let's plot a quadratic function
    if (y[i] < this->smallest) this->smallest = y[i];
    if (y[i] > this->largest) this->largest = y[i];
  }
  // add data to the Xs and Ys database
  this->Xs.append(x);
  this->Ys.append(y);
  // create graph and assign data to every graph:
  customPlot->addGraph();
  for (int i = 0; i < this->Xs.size(); i++){
      customPlot->graph(i)->setData(Xs.at(i), Ys.at(i));
  }
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-this->range, this->range);
  customPlot->yAxis->setRange(this->smallest, this->largest);
  customPlot->savePng("Test.png",500,500);
  emit load();

}

void FuncWindow::setupSinusoidalDemo(QCustomPlot *customPlot)
{
  // generate some data:
  QVector<double> x(10000*this->range+1), y(10000*this->range+1); // initialize with entries 0..10000*range
  for (int i=0; i<10000*this->range+1; ++i)
  {
    x[i] = 1.0*i/5000 - this->range; // x goes from -range to range
    y[i] = this->SinA*sin(this->omega*x[i]+this->fhi)+this->C;  // let's plot a sin function
    if (y[i] < this->smallest) this->smallest = y[i];
    if (y[i] > this->largest) this->largest = y[i];
  }
  // add data to the Xs and Ys database
  this->Xs.append(x);
  this->Ys.append(y);
  // create graph and assign data to every graph:
  customPlot->addGraph();
  for (int i = 0; i < this->Xs.size(); i++){
      customPlot->graph(i)->setData(Xs.at(i), Ys.at(i));
  }
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-this->range, this->range);
  customPlot->yAxis->setRange(this->smallest, this->largest);
  customPlot->savePng("Test.png",500,500);
}

void FuncWindow::setupExponentialDemo(QCustomPlot *customPlot)
{
  // generate some data:
  QVector<double> x(10000*this->range+1), y(10000*this->range+1); // initialize with entries 0..10000*range
  for (int i=0; i<10000*this->range+1; ++i)
  {
    x[i] = 1.0*i/5000 - this->range; // x goes from -range to range
    y[i] = this->ExpA*exp(this->alpha*x[i]);  // let's plot a exponential function
    if (y[i] < this->smallest) this->smallest = y[i];
    if (y[i] > this->largest) this->largest = y[i];
  }
  // add data to the Xs and Ys database
  this->Xs.append(x);
  this->Ys.append(y);
  // create graph and assign data to every graph:
  customPlot->addGraph();
  for (int i = 0; i < this->Xs.size(); i++){
      customPlot->graph(i)->setData(Xs.at(i), Ys.at(i));
  }
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-this->range, this->range);
  customPlot->yAxis->setRange(this->smallest, this->largest);
  customPlot->savePng("Test.png",500,500);
}


void FuncWindow::on_pushButton_clicked()
{
    // receive parameters and plot a quadratic function
    this->a = ui->lineEdit->text().toDouble();
    this->b = ui->lineEdit_2->text().toDouble();
    this->c = ui->lineEdit_3->text().toDouble();
    this->range = ui->lineEdit_4->text().toDouble();
    setupQuadraticDemo(ui->customPlot);
    ui->customPlot->replot();
}

void FuncWindow::on_pushButton_4_clicked()
{
    // receive parameters and plot a sin function
    this->SinA = ui->lineEdit_13->text().toDouble();
    this->omega = ui->lineEdit_14->text().toDouble();
    this->fhi = ui->lineEdit_15->text().toDouble();
    this->C = ui->lineEdit_21->text().toDouble();
    this->range = ui->lineEdit_16->text().toDouble();
    setupSinusoidalDemo(ui->customPlot);
    ui->customPlot->replot();
}

void FuncWindow::on_pushButton_5_clicked()
{
    // receive parameters and plot a exponential function
    this->ExpA = ui->lineEdit_17->text().toDouble();
    this->alpha = ui->lineEdit_18->text().toDouble();
    this->range = ui->lineEdit_20->text().toDouble();
    setupExponentialDemo(ui->customPlot);
    ui->customPlot->replot();
}

void FuncWindow::on_pushButton_6_clicked()
{
    // clear all parameters and all graphs
    this->Xs.clear();
    this->Ys.clear();
    this->smallest = 100000000;
    this->largest = -100000000;
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
}


void FuncWindow::on_pushButton_2_clicked()
{
    emit loadPlot();
    emit load();
    qDebug()<<"emit";

}

