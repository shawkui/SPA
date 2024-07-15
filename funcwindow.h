#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class FuncWindow;
}

class FuncWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FuncWindow(QWidget *parent = 0);
    ~FuncWindow();
    void setupQuadraticDemo(QCustomPlot *customPlot);
    void setupSinusoidalDemo(QCustomPlot *customPlot);
    void setupExponentialDemo(QCustomPlot *customPlot);

signals:
    void load();
    void loadPlot();

private:
    Ui::FuncWindow *ui;
    double a,b,c;                // parameters of quadratic function
    double ExpA, alpha;          // parameters of exponential function
    double SinA, omega, fhi, C;  // parameters of sin function
    double range;                // range of x
    double smallest = 100000000;  // store the smallest y value of all functions
    double largest = -100000000;  // store the largest y value of all functions
    QVector <QVector <double>> Xs, Ys;  // store x values and y values of all functions

private slots:
    void on_pushButton_clicked();  // To plot a quadratic function
    void on_pushButton_4_clicked(); // To plot a sin function
    void on_pushButton_5_clicked(); // To plot a exponential function
    void on_pushButton_6_clicked(); // Clear graphs of all functions
    void on_pushButton_2_clicked();
};

#endif // FUNCWINDOW_H
