#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogprofile.h"

#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QScatterSeries>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _a(500),
    _P(100),
    _B(65),
    _H(110),
    _b(50),
    _h(80),
    _sH(110),
    _sB(65),
    _l(3000),
    _p(7800),
    _E(190000 * 1e6)
{
    bluePen.setColor(0x117bb9);
    bluePen.setWidth(2);

    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.8);

    ui->label_15->setText(QString::number(Mass1(_sH, _sB)) + " кг");
    ui->label_25->setText(QString::number(Mass2(_H, _B, _h, _b)) + " кг");

    connect(ui->action, &QAction::triggered, this, &MainWindow::openProfileDialog);

    /*
     *  Инициализация графиков и эпюр
     */

    _qChartView = new QChartView(buildQChart());
    _qChartView->setRenderHint(QPainter::Antialiasing);
    _mChartView = new QChartView(buildMChart());
    _mChartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *horisontalLayout = new QHBoxLayout;
    QWidget *horisontalWidget = new QWidget;
    horisontalLayout->addWidget(_qChartView);
    horisontalLayout->addWidget(_mChartView);
    horisontalWidget->setLayout(horisontalLayout);
    ui->tab->layout()->addWidget(horisontalWidget);

    _w1ChartView = new QChartView(buildW1Chart());
    _w1ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_2->layout()->addWidget(_w1ChartView);

    _w2ChartView = new QChartView(buildW2Chart());
    _w2ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_2->layout()->addWidget(_w2ChartView);

    _a1ChartView = new QChartView(buildA1Chart());
    _a1ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_3->layout()->addWidget(_a1ChartView);

    _a2ChartView = new QChartView(buildA2Chart());
    _a2ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_3->layout()->addWidget(_a2ChartView);

    _f1ChartView = new QChartView(buildF1Chart());
    _f1ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_4->layout()->addWidget(_f1ChartView);

    _f2ChartView = new QChartView(buildF2Chart());
    _f2ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_4->layout()->addWidget(_f2ChartView);

    _s1ChartView = new QChartView(buildS1Chart());
    _s1ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_5->layout()->addWidget(_s1ChartView);

    _s2ChartView = new QChartView(buildS2Chart());
    _s2ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_5->layout()->addWidget(_s2ChartView);

    _sig1ChartView = new QChartView(buildSig1Chart());
    _sig1ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_6->layout()->addWidget(_sig1ChartView);

    _sig2ChartView = new QChartView(buildSig2Chart());
    _sig2ChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_6->layout()->addWidget(_sig2ChartView);

    _profileSizeChartView = new QChartView(buildProfileSizeChart());
    _profileSizeChartView->setRenderHint(QPainter::Antialiasing);
    ui->tab_7->layout()->addWidget(_profileSizeChartView);

    _profileSizeChartView->setMinimumWidth(600);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QChart *MainWindow::buildQChart()
{
    QLineSeries *qSeries = new QLineSeries();
    QLineSeries *qSeriesAx = new QLineSeries();

    // Расчет значений

    for (double z = 0; z < _a; z += 1) qSeries->append(z, -_P);
    for (double z = _a; z < _a + _l; z += 1) qSeries->append(z, 0);
    for (double z = _a + _l; z < _l + 2 * _a; z += 1) qSeries->append(z, _P);

    qSeriesAx->append(0,0);
    qSeriesAx->append(_l + 2 * _a,0);

     // Визуальные изменения (толщина обводки, названия и тд)

    QAreaSeries *series = new QAreaSeries(qSeries, qSeriesAx);

    QPen pen(0x059605);
    pen.setWidth(2);
    series->setPen(pen);
    series->setBrush(Qt::VerPattern);

    QChart *qChart = new QChart();
    qChart->addSeries(series);
    qChart->createDefaultAxes();
    qChart->setTitle("Эпюра Q(z)");
    qChart->axisX()->setTitleText("Длина, мм");
    qChart->axisY()->setTitleText("Поперечная сила, Н");
    qChart->legend()->hide();

    return qChart;
}

QChart *MainWindow::buildMChart()
{
    QLineSeries *mSeries = new QLineSeries();
    QLineSeries *qSeriesAx = new QLineSeries();

    // Расчет значений

    for (double z = 0; z <= _a; z += 1) mSeries->append(z, -_P * z * 1e-3);
    for (double z = _a; z <= _a + _l; z += 1) mSeries->append(z, -_P * _a * 1e-3);
    for (double z = _a + _l; z <= _l + 2 * _a; z += 1) mSeries->append(z, -_P * (_l * 1e-3 + 2 * _a * 1e-3 - z * 1e-3));

    // Визуальные изменения (толщина обводки, названия и тд)

    qSeriesAx->append(0,0);
    qSeriesAx->append(_l + _a,0);

    QAreaSeries *series = new QAreaSeries(mSeries, qSeriesAx);

    QPen pen(0x059605);
    pen.setWidth(2);
    series->setPen(pen);
    series->setBrush(Qt::VerPattern);

    QChart *mChart = new QChart();
    mChart->addSeries(series);
    mChart->createDefaultAxes();
    mChart->setTitle("Эпюра M(z)");
    mChart->axisX()->setTitleText("Длина, мм");
    mChart->axisY()->setTitleText("Изгибающий момент, Н﹒м");
    mChart->legend()->hide();

    return mChart;
}

QChart *MainWindow::buildW1Chart()
{
    QLineSeries *w1Series = new QLineSeries();

    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J1(_sB * 1e-3, _sH * 1e-3);

    for (double z = 0; z < _a; z += 1) {
        double w1 = -(_P * pow(a, 2) / (6 * _E * j)) * ((3 * l + 2 * a) - 3 * (l + a) * ((z * 1e-3) / a) + pow(z * 1e-3, 3) / pow(a, 2) );
        w1Series->append(z, w1 * 1e3);
    }

    for (double z = _a; z < _l + _a; z += 1) {
        double w1 = -(_P * pow(a, 2) / (6 * _E * j)) * ((3 * l + 2 * a) - 3 * (l + a) * ((z * 1e-3) / a) + (pow(z * 1e-3, 3) / pow(a, 2)) - (pow((z * 1e-3) - a, 3) / pow(a, 2)) );
        w1Series->append(z, w1 * 1e3);
    }

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *w1Chart = new QChart();
    w1Series->setPen(bluePen);
    w1Chart->addSeries(w1Series);
    w1Chart->createDefaultAxes();
    w1Chart->setTitle("Изгиб w(z) для сплошного сечения");
    w1Chart->axisY()->setTitleText("Изгиб, мм");
    w1Chart->axisX()->setTitleText("Длина, мм");
    w1Chart->legend()->hide();

    return w1Chart;
}

QChart *MainWindow::buildW2Chart()
{
    QLineSeries *w2Series = new QLineSeries();

    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J2(_B * 1e-3, _H * 1e-3, _b * 1e-3, _h * 1e-3);

    for (double z = 0; z < _a; z += 1) {
        double w2 = -(_P * pow(a, 2) / (6 * _E * j)) * ((3 * l + 2 * a) - 3 * (l + a) * ((z * 1e-3) / a) + pow(z * 1e-3, 3) / pow(a, 2) );
        w2Series->append(z, w2 * 1e3);
    }

    for (double z = _a; z <_l + _a; z += 1) {
        double w2 = -(_P * pow(a, 2) / (6 * _E * j)) * ((3 * l + 2 * a) - 3 * (l + a) * ((z * 1e-3) / a) + (pow(z * 1e-3, 3) / pow(a, 2)) - (pow((z * 1e-3) - a, 3) / pow(a, 2)) );
        w2Series->append(z, w2 * 1e3);
    }

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *w2Chart = new QChart();
    w2Series->setPen(bluePen);
    w2Chart->addSeries(w2Series);
    w2Chart->createDefaultAxes();
    w2Chart->setTitle("Изгиб w(z) для полого сечения");
    w2Chart->axisY()->setTitleText("Изгиб, мм");
    w2Chart->axisX()->setTitleText("Длина, мм");
    w2Chart->legend()->hide();

    return w2Chart;
}

QChart *MainWindow::buildA1Chart()
{
    QLineSeries *a1Series = new QLineSeries();

    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J1(_sB * 1e-3, _sH * 1e-3);

    for (double z = 0; z < _a; z += 1) {
        double a1 = _P * (pow(a, 2) + a * l - pow(z * 1e-3, 2)) / (2 * _E * j);
        a1Series->append(z, a1 * 1e4);
    }

    for (double z = _a; z < _l + _a; z += 1) {
        double a1 = a * _P * (2 * a + l - (2 * z * 1e-3)) / (2 * _E * j);
        a1Series->append(z, a1 * 1e4);
    }

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *a1Chart = new QChart();
    a1Series->setPen(bluePen);
    a1Chart->addSeries(a1Series);
    a1Chart->createDefaultAxes();
    a1Chart->setTitle("Угол поворота Θ(z) для сплошного сечения");
    a1Chart->axisY()->setTitleText("Угол, рад ᐧ 10⁻⁴");
    a1Chart->axisX()->setTitleText("Длина, мм");
    a1Chart->legend()->hide();

    return a1Chart;
}

QChart *MainWindow::buildA2Chart()
{
    QLineSeries *a2Series = new QLineSeries();

    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J2(_B * 1e-3, _H * 1e-3, _b * 1e-3, _h * 1e-3);

    for (double z = 0; z < _a; z += 1) {
        double a2 = _P * (pow(a, 2) + a * l - pow(z * 1e-3, 2)) / (2 * _E * j);
        a2Series->append(z, a2 * 1e4);
    }

    for (double z = _a; z < _l + _a; z += 1) {
        double a2 = a * _P * (2 * a + l - (2 * z * 1e-3)) / (2 * _E * j);
        a2Series->append(z, a2 * 1e4);
    }

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *a2Chart = new QChart();
    a2Series->setPen(bluePen);
    a2Chart->addSeries(a2Series);
    a2Chart->createDefaultAxes();
    a2Chart->setTitle("Угол поворота Θ(z) для полого сечения");
    a2Chart->axisY()->setTitleText("Угол, рад ᐧ 10⁻⁴");
    a2Chart->axisX()->setTitleText("Длина, мм");
    a2Chart->legend()->hide();

    return a2Chart;
}

QChart *MainWindow::buildF1Chart()
{
    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J1(_sB * 1e-3, _sH * 1e-3);

    QLineSeries *f1Series = new QLineSeries();
    for (double p = 0; p <= _P; p++)
    f1Series->append(p, (p * a * pow(l, 2) / (8 * _E * j)) * 1e3);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *f1Chart = new QChart();
    f1Series->setPen(bluePen);
    f1Chart->addSeries(f1Series);
    f1Chart->createDefaultAxes();
    f1Chart->setTitle("Максимальный прогиб f(q) для сплошного сечения при z = a + l/2");
    f1Chart->axisY()->setTitleText("Прогиб, мм ");
    f1Chart->axisX()->setTitleText("Нагрузка, Н");
    f1Chart->legend()->hide();

    return f1Chart;
}

QChart *MainWindow::buildF2Chart()
{
    // Расчет значений

    // Перевод в СИ
    double a = _a * 1e-3;
    double l = _l * 1e-3;
    double j = J2(_B * 1e-3, _H * 1e-3, _b * 1e-3, _h * 1e-3);

    QLineSeries *f2Series = new QLineSeries();
    for (double p = 0; p <= _P; p++)
    f2Series->append(p, (p * a * pow(l, 2) / (8 * _E * j)) * 1e3);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *f2Chart = new QChart();
    f2Series->setPen(bluePen);
    f2Chart->addSeries(f2Series);
    f2Chart->createDefaultAxes();
    f2Chart->setTitle("Максимальный прогиб f(q) для сплошного сечения при z = a + l/2");
    f2Chart->axisY()->setTitleText("Прогиб, мм ");
    f2Chart->axisX()->setTitleText("Нагрузка, Н");
    f2Chart->legend()->hide();

    return f2Chart;
}

QChart *MainWindow::buildS1Chart()
{
    // Расчет значений

    QLineSeries *s1Series = new QLineSeries();
    for (double f = 0; f < _P; f++) s1Series->append(f, S1(f) * 1e-6);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *s1Chart = new QChart();
    s1Series->setPen(bluePen);
    s1Chart->addSeries(s1Series);
    s1Chart->createDefaultAxes();
    s1Chart->setTitle("Максимальное напряжение σ(P) для сплошного сечения при z = l");
    s1Chart->axisY()->setTitleText("Напряжение, МПа");
    s1Chart->axisX()->setTitleText("Нагрузка, Н");
    s1Chart->legend()->hide();

    return s1Chart;
}

QChart *MainWindow::buildS2Chart()
{
    // Расчет значений

    QLineSeries *s2Series = new QLineSeries();
    for (double f = 0; f < _P; f++) s2Series->append(f, S2(f) * 1e-6);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *s2Chart = new QChart();
    s2Series->setPen(bluePen);
    s2Chart->addSeries(s2Series);
    s2Chart->createDefaultAxes();
    s2Chart->setTitle("Максимальное напряжение σ(P) для полого сечения при z = l");
    s2Chart->axisY()->setTitleText("Напряжение, МПа");
    s2Chart->axisX()->setTitleText("Нагрузка, Н");
    s2Chart->legend()->hide();

    return s2Chart;
}

double MainWindow::J1(double B, double H)
{
    return (B * H * (9600 - 21600 * H + 14009 * pow(H, 2))) / 1297920;
}

double MainWindow::J2(double B, double H, double b, double h)
{
    return (B * H * (516977 * pow(H,2) - 1703520 * H + 1622400))/147107450 - (b * h * (1622400 - 1703520 * h + 516977 * pow(h,2)))/147107450;
}

QChart *MainWindow::buildSig1Chart()
{
    // Расчет значений

    QLineSeries *sig1Series = new QLineSeries();
    for (double r = _sB * _sH * 0.1; r < _sB * _sH; r++) sig1Series->append(M1(r), Sig1(r*1e-6) * 1e-6);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *sig1Chart = new QChart();
    sig1Series->setPen(bluePen);
    sig1Chart->addSeries(sig1Series);
    sig1Chart->createDefaultAxes();
    sig1Chart->setTitle("Максимальное напряжение σ(m) для сплошного сечения");
    sig1Chart->axisY()->setTitleText("Напряжение σ, МПа");
    sig1Chart->axisX()->setTitleText("Масса m, Кг");
    sig1Chart->legend()->hide();

    return sig1Chart;
}

QChart *MainWindow::buildSig2Chart()
{
    // Расчет значений

    QLineSeries *sig2Series = new QLineSeries();
    for (double r = _B * _H * 0.1; r < _B * _H; r++) sig2Series->append(M2(r), Sig2(r*1e-6) * 1e-6);

    // Визуальные изменения (толщина обводки, названия и тд)

    QChart *sig2Chart = new QChart();
    sig2Series->setPen(bluePen);
    sig2Chart->addSeries(sig2Series);
    sig2Chart->createDefaultAxes();
    sig2Chart->setTitle("Максимальное напряжение σ(m) для полого сечения");
    sig2Chart->axisY()->setTitleText("Напряжение σ, МПа");
    sig2Chart->axisX()->setTitleText("Масса m, Кг");
    sig2Chart->legend()->hide();

    return sig2Chart;
}

QChart *MainWindow::buildProfileSizeChart()
{
    // Расчет значений

    QChart *profileSizeChart = new QChart();
    double minMass = Mass1(2 * _sH, 2 * _sB);

    for (double h = 0; h <= _sH; h += 1) {
        for (double b = 0; b <= _sB; b += 1) {
            for (double H = _sH; H <= 2 * _sH; H += 1) {
                if (B(H, h, b) <= 2 * _sB && B(H, h, b) >= _sB) {
                    if (((H == _sH || H == (2 * _sH)) && (B(H, h, b) >= _sB && B(H, h, b) <= (2 * _sB)))
                            || ((B(H, h, b) == _sB || B(H, h, b) == (2 * _sB)) && (H >= _sH && H <= (2 * _sH)))) {
                        double oldMass = minMass;
                        minMass = qMin(minMass, Mass2(H, B(H, h, b), h, b));
                        if (oldMass != minMass) {
                            _oB = B(H, h, b); _oH = H; _ob = b; _oh = h;
                        }
                    }
                }
            }
        }
    }

    // Построение кривых и точек потенциальных значений

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setMarkerSize(10.0);
    series1->setColor(0xafafaf);
    profileSizeChart->addSeries(series1);

    for (double h = 0; h < 2 * _sH; h += _sH / 2.0 ) {
        for (double b = 0; b < 2 * _sB; b += _sH / 2.0) {
            QLineSeries *s = new QLineSeries();
            s->setColor(0xafafaf);
            for (double H = 0; H < 3 * _sH; H += 1) {
                s->append(H, B(H, h, b));
                if (((H == _sH || H == (2 * _sH)) && (B(H, h, b) >= _sB && B(H, h, b) <= (2 * _sB)))
                        || ((abs(B(H, h, b) - _sB) < 1e-5 || abs(B(H, h, b) - (2 * _sB)) < 1e-5) && (H >= _sH && H <= (2 * _sH)))) {
                     series1->append(H, B(H, h, b));
                }
            }
            profileSizeChart->addSeries(s);
        }
    }

    // Построение кривой оптимальных значений

    QLineSeries *optimalSeries = new QLineSeries();
    for (double k = 0; k < 3 * _sH; k += 1) optimalSeries->append(k, B(k, _oh, _ob));
    optimalSeries->setColor(0xff0000);
    QPen optimalPen(0xff0000);
    optimalPen.setWidth(3);
    optimalSeries->setPen(optimalPen);
    profileSizeChart->addSeries(optimalSeries);

    // Построение точки оптимального значения

    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);
    series0->setColor(0xff0000);
    series0->append(_oH, _oB);
    profileSizeChart->addSeries(series0);
    profileSizeChart->createDefaultAxes();
    profileSizeChart->setTitle("Зависимость высоты от ширины бруса для полого сечения");
    profileSizeChart->axisX()->setTitleText("Высота H, mm");
    profileSizeChart->axisY()->setTitleText("Ширина B, mm");

    auto aX = (QValueAxis*)profileSizeChart->axisX();
    aX->setTickCount(4);

    auto aY = (QValueAxis*)profileSizeChart->axisY();
    aY->setTickCount(4);

    profileSizeChart->axisY()->setRange(0, 3 * _sB);
    profileSizeChart->axisX()->setRange(0, 3 * _sH);

    auto markers = profileSizeChart->legend()->markers();
    for (auto &marker : markers) {
        marker->setVisible(false);
    }

    markers.first()->setVisible(true);
    markers.first()->setLabel("Потенциальные значения");

    markers.last()->setVisible(true);
    markers.last()->setLabel("Оптимальные значения");


    ui->label_17->setText(QString::number(minMass) + ", Кг");
    ui->lineEdit_11->setText(QString::number(_oB));
    ui->lineEdit_12->setText(QString::number(_oH));
    ui->lineEdit_14->setText(QString::number(_ob));
    ui->lineEdit_15->setText(QString::number(_oh));

    return profileSizeChart;
}

double MainWindow::S1(double p)
{
    double yMax = _sH * 1e-3 / 2.0;

    double M = -p * _a * 1e-3;

    return (M * yMax) / J1(_sB * 1e-3, _sH * 1e-3);

}

double MainWindow::S2(double p)
{
    double yMax = _H * 1e-3 / 2.0;

    double M = -p * _a * 1e-3;

    return (M * yMax) / J2(_B * 1e-3, _H * 1e-3, _b * 1e-3, _h * 1e-3);
}

double MainWindow::S(double p, double H, double B, double h, double b)
{
    double yMax = H * 1e-3 / 2.0;

    double M = -p * _a * 1e-3;

    return (M * yMax) / J2(B * 1e-3, H * 1e-3, b * 1e-3, h * 1e-3);
}

double MainWindow::Sig1(double R)
{
    double B = _B * 1e-3, H = _H * 1e-3;
    double K = B/H;
    double tH = sqrt(R/K), tB = R/H;

    return (-_P * pow(_l, 2) * tH * 1e-6) / (12.0 * J1(tB, tH));
}

double MainWindow::Sig2(double R)
{
    double B = _B * 1e-3, H = _H * 1e-3, b = _b * 1e-3, h = _h * 1e-3;
    double K = B/H, Kkb = B/b, Kkh = H/h;
    double tH = sqrt(R/K), tB = R/H, tb = tB/Kkb, th = tH/Kkh;

    return (-_P * pow(_l, 2) * tH * 1e-6) / (12.0 * J2(tB, tH, tb, th));
}

double MainWindow::M1(double R)
{
    double B = _B, H = _H;
    double K = B/H;
    double tH = sqrt(R/K), tB = R/H;
    return Mass1(tH,tB);
}

double MainWindow::M2(double R)
{
    double B = _B, H = _H, b = _b, h = _h;
    double K = B/H, Kkb = B/b, Kkh = H/h;
    double tH = sqrt(R/K), tB = R/H, tb = tB/Kkb, th = tH/Kkh;
    return Mass2(tH,tB,th,tb);
}

double MainWindow::B(double H, double h, double b)
{
    return ((516977 * pow(_sH,2) - 1703520 * _sH + 1622400) * _sB * H + b * h * (516977 * pow(h,2) - 1703520 * h + 1622400))/(H * (516977 * pow(H,2) - 1703520 * H + 1622400));
}

double MainWindow::Mass1(double H, double B)
{
    return (_l * 1e-3 * _p) * (5.0 * B * H * 1e-6 / 8.0);
}

double MainWindow::Mass2(double H, double B, double h, double b)
{
    return (_l * 1e-3 * _p) * (13.0 / 16.0 * (B * H - b * h) * 1e-6);
}

void MainWindow::openProfileDialog()
{
    DialogProfile dlg;
    dlg.setValues(_h, _b, _H, _B);
    dlg.setModal(true);
    dlg.exec();

    _b = dlg.b;
    _h = dlg.h;
    _B = dlg.B;
    _H = dlg.H;

    ui->lineEdit_9->setText(QString::number(_B));
    ui->lineEdit_10->setText(QString::number(_H));
    ui->lineEdit_13->setText(QString::number(_b));
    ui->lineEdit_16->setText(QString::number(_h));

    updateCharts();
}

void MainWindow::updateCharts()
{
    /*
     *  Здесь пересчитываем координаты функции для новых параметров и обновляем их в графике
     */

    _qChartView->setChart(buildQChart());
    _mChartView->setChart(buildMChart());
    _w1ChartView->setChart(buildW1Chart());
    _w2ChartView->setChart(buildW2Chart());
    _a1ChartView->setChart(buildA1Chart());
    _a2ChartView->setChart(buildA2Chart());
    _f1ChartView->setChart(buildF1Chart());
    _f2ChartView->setChart(buildF2Chart());
    _s1ChartView->setChart(buildS1Chart());
    _s2ChartView->setChart(buildS2Chart());
    _sig1ChartView->setChart(buildSig1Chart());
    _sig2ChartView->setChart(buildSig2Chart());
    _profileSizeChartView->setChart(buildProfileSizeChart());

    /*
     *  Здесь пересчитываем координаты функции для новых параметров и обновляем их в графике
     */
}

void MainWindow::on_pushButton_clicked()
{
    _P = ui->lineEdit->text().toDouble();
    ui->lineEdit_2->setText(QString::number(_P));
    ui->lineEdit_3->setText(QString::number(_P));
    ui->lineEdit_4->setText(QString::number(_P));
    ui->lineEdit_5->setText(QString::number(_P));
    ui->lineEdit_6->setText(QString::number(_P));

    _a = ui->lineEdit_17->text().toDouble();
    ui->lineEdit_18->setText(QString::number(_a));
    ui->lineEdit_19->setText(QString::number(_a));
    ui->lineEdit_20->setText(QString::number(_a));
    ui->lineEdit_21->setText(QString::number(_a));
    ui->lineEdit_22->setText(QString::number(_a));

    updateCharts();
}

void MainWindow::on_pushButton_2_clicked()
{
    _P = ui->lineEdit_2->text().toDouble();
    ui->lineEdit->setText(QString::number(_P));
    ui->lineEdit_3->setText(QString::number(_P));
    ui->lineEdit_4->setText(QString::number(_P));
    ui->lineEdit_5->setText(QString::number(_P));
    ui->lineEdit_6->setText(QString::number(_P));

    _a = ui->lineEdit_18->text().toDouble();
    ui->lineEdit_17->setText(QString::number(_a));
    ui->lineEdit_19->setText(QString::number(_a));
    ui->lineEdit_20->setText(QString::number(_a));
    ui->lineEdit_21->setText(QString::number(_a));
    ui->lineEdit_22->setText(QString::number(_a));

    updateCharts();
}

void MainWindow::on_pushButton_3_clicked()
{
    _P = ui->lineEdit_3->text().toDouble();
    ui->lineEdit->setText(QString::number(_P));
    ui->lineEdit_2->setText(QString::number(_P));
    ui->lineEdit_4->setText(QString::number(_P));
    ui->lineEdit_5->setText(QString::number(_P));
    ui->lineEdit_6->setText(QString::number(_P));

    _a = ui->lineEdit_19->text().toDouble();
    ui->lineEdit_17->setText(QString::number(_a));
    ui->lineEdit_18->setText(QString::number(_a));
    ui->lineEdit_20->setText(QString::number(_a));
    ui->lineEdit_21->setText(QString::number(_a));
    ui->lineEdit_22->setText(QString::number(_a));

    updateCharts();
}

void MainWindow::on_pushButton_4_clicked()
{
    _P = ui->lineEdit_4->text().toDouble();
    ui->lineEdit->setText(QString::number(_P));
    ui->lineEdit_2->setText(QString::number(_P));
    ui->lineEdit_3->setText(QString::number(_P));
    ui->lineEdit_5->setText(QString::number(_P));
    ui->lineEdit_6->setText(QString::number(_P));

    _a = ui->lineEdit_20->text().toDouble();
    ui->lineEdit_17->setText(QString::number(_a));
    ui->lineEdit_18->setText(QString::number(_a));
    ui->lineEdit_19->setText(QString::number(_a));
    ui->lineEdit_21->setText(QString::number(_a));
    ui->lineEdit_22->setText(QString::number(_a));

    updateCharts();

}

void MainWindow::on_pushButton_5_clicked()
{
    _P = ui->lineEdit_5->text().toDouble();
    ui->lineEdit->setText(QString::number(_P));
    ui->lineEdit_2->setText(QString::number(_P));
    ui->lineEdit_3->setText(QString::number(_P));
    ui->lineEdit_4->setText(QString::number(_P));
    ui->lineEdit_6->setText(QString::number(_P));

    _a = ui->lineEdit_21->text().toDouble();
    ui->lineEdit_17->setText(QString::number(_a));
    ui->lineEdit_18->setText(QString::number(_a));
    ui->lineEdit_19->setText(QString::number(_a));
    ui->lineEdit_20->setText(QString::number(_a));
    ui->lineEdit_22->setText(QString::number(_a));

    updateCharts();
}

void MainWindow::on_pushButton_6_clicked()
{
    _P = ui->lineEdit_6->text().toDouble();
    ui->lineEdit->setText(QString::number(_P));
    ui->lineEdit_2->setText(QString::number(_P));
    ui->lineEdit_3->setText(QString::number(_P));
    ui->lineEdit_4->setText(QString::number(_P));
    ui->lineEdit_5->setText(QString::number(_P));

    _a = ui->lineEdit_22->text().toDouble();
    ui->lineEdit_17->setText(QString::number(_a));
    ui->lineEdit_18->setText(QString::number(_a));
    ui->lineEdit_19->setText(QString::number(_a));
    ui->lineEdit_20->setText(QString::number(_a));
    ui->lineEdit_21->setText(QString::number(_a));

    updateCharts();
}

void MainWindow::on_pushButton_7_clicked()
{
    _sB = ui->lineEdit_7->text().toDouble();
    _sH = ui->lineEdit_8->text().toDouble();
    _B = ui->lineEdit_9->text().toDouble();
    _H = ui->lineEdit_10->text().toDouble();
    _h = ui->lineEdit_13->text().toDouble();
    _b = ui->lineEdit_16->text().toDouble();

    ui->label_15->setText(QString::number(Mass1(_sH, _sB)) + " кг");
    ui->label_17->setText(QString::number(Mass2(_oH, _oB, _oh, _ob)) + " кг");
    ui->label_25->setText(QString::number(Mass2(_H, _B, _h, _b)) + " кг");

    updateCharts();
}
