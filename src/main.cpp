#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    if (myappTranslator.load(QLocale::system(), "brasilcov", "_", ":/lang"))
        app.installTranslator(&myappTranslator);

    MainWindow mainwindow(&myappTranslator);
    mainwindow.show();

    return app.exec();
}