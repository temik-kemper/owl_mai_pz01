#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>
#include <QDateTime>
#include <QTextStream>
#include "myrandom.h"
#include "cvectordft.h"
#include <math.h>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QAreaSeries>

#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

#define SIZE 10
#define GIST_SIZE 20

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MyRandom rnd;

    QLineSeries *serSamples;
    QChart *chartSamples;

    QLineSeries *serGist;
    QChart *chartGist;

    QLineSeries *serCor;
    QChart *chartCor;

    QLineSeries *serSpectr;
    QChart *chartSpectr;

void InitChart(QWidget *parent,QChart *chart,QString title="",QString y_title="",QString x_title="");

protected:
    void timerEvent(QTimerEvent *);
    void ShowComplexGist(complex*, int arrSize);

private slots:
    void on_btTest01_clicked();
    void on_btRndInit_clicked();
    void on_btTest02_clicked();

    void on_btRndSamplesShow_clicked();
    void on_btGrSamplesClear_clicked();

    void on_btRndGistShow_clicked();
    void on_btRndGistClear_clicked();

    void on_btRndCorShow_clicked();
    void on_btRndCorClear_clicked();
};
#endif // MAINWINDOW_H
