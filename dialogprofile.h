#ifndef DIALOGPROFILE_H
#define DIALOGPROFILE_H

#include <QDialog>

namespace Ui {
class DialogProfile;
}

class DialogProfile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProfile(QWidget *parent = nullptr);
    ~DialogProfile();

    void setValues(double h, double b, double H, double B);
    double h, b, H, B;

private:
    Ui::DialogProfile *ui;

private slots:
    void saveInput();
};

#endif // DIALOGPROFILE_H
