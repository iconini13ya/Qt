#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QPen>
#include <cmath>

QT_CHARTS_USE_NAMESPACE

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QChartView *_qChartView;
    QChartView *_mChartView;
    QChartView *_w1ChartView;
    QChartView *_w2ChartView;
    QChartView *_a1ChartView;
    QChartView *_a2ChartView;
    QChartView *_f1ChartView;
    QChartView *_f2ChartView;
    QChartView *_s1ChartView;
    QChartView *_s2ChartView;
    QChartView *_sig1ChartView;
    QChartView *_sig2ChartView;
    QChartView *_profileSizeChartView;

    QChart *buildQChart(); // Расчет и построение эпюры Q
    QChart *buildMChart(); // Расчет и построение эпюры M
    QChart *buildW1Chart(); // Расчет и построение графика изгиба w(z) для сплошного сечения
    QChart *buildW2Chart(); // Расчет и построение графика изгиба w(z) для полого сечения
    QChart *buildA1Chart(); // Расчет и построение графика угла поврота Θ(z) для сплошного сечения
    QChart *buildA2Chart(); // Расчет и построение графика угла поврота Θ(z) для полого сечения
    QChart *buildF1Chart(); // Расчет и построение графика максимального прогиба f(q) для сплошного сечения
    QChart *buildF2Chart(); // Расчет и построение графика максимального прогиба f(q) для полого сечения
    QChart *buildS1Chart(); // Расчет и построение графика макс. напряжения от нагрузки σ(q) для сплошного сечения
    QChart *buildS2Chart(); // Расчет и построение графика макс. напряжения от нагрузки σ(q) для полого сечения
    QChart *buildSig1Chart(); // Расчет и построение графика макс. напряжения от массы σ(m) для сплошного сечения
    QChart *buildSig2Chart(); // Расчет и построение графика макс. напряжения от массы σ(m) для полого сечения
    QChart *buildProfileSizeChart(); // Расчет оптимального профиля сечения, массы и построения графиков зависимостей ширины от высоты

    QPen bluePen;

    double J1(double b, double h); // Момент инерции для сплошного сечения
    double J2(double B, double H, double b, double h); // Момент инерции для полого сечения

    double S1(double q); // Напряжение от нагрузки для сплошного сечения
    double S2(double q); // Напряжение от нагрузки для полого сечения
    double S(double q, double H, double B, double h, double b);
    double Sig1(double R); // Напряжение от массы для сплошного сечения
    double Sig2(double R); // Напряжение от массы для полого сечения
    double M1(double R); // Масса от площади для сплошного сечения
    double M2(double R); // Масса от площади для полого сечения
    double B(double H, double h, double b); // Зависимость ширины от высоты и размеров отверстий
    double Mass1(double H, double B); // Масса для сплошного сечения
    double Mass2(double H, double B, double h, double b); // Масса для полого сечения

    double _a, _P, _l, _E, _p;

    double _B, _H, _b, _h; // Размеры полого сечения
    double _oB, _oH, _ob, _oh; // Размеры оптимального сечения
    double _sB, _sH; // Размеры сплошного сечения

private slots:
    void openProfileDialog(); // Функция для открытия диалога
    void updateCharts(); // Перерисовка графиков с новыми параметрами

    // Обработчики событий для кнопок
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
};

#endif // MAINWINDOW_H
