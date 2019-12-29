#include "dialogprofile.h"
#include "ui_dialogprofile.h"

DialogProfile::DialogProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfile),
    h(50),
    b(50),
    H(160),
    B(95)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogProfile::saveInput);
}

DialogProfile::~DialogProfile()
{
    delete ui;
}

void DialogProfile::setValues(double h, double b, double H, double B)
{
    ui->lineEdit->setText(QString::number(h));
    ui->lineEdit_2->setText(QString::number(b));
    ui->lineEdit_4->setText(QString::number(H));
    ui->lineEdit_3->setText(QString::number(B));

}

void DialogProfile::saveInput()
{
    h = ui->lineEdit->text().toDouble();
    b = ui->lineEdit_2->text().toDouble();
    H = ui->lineEdit_4->text().toDouble();
    B = ui->lineEdit_3->text().toDouble();

}
