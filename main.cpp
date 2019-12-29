#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

        MainWindow window;
        window.show();

    return a.exec();
}
