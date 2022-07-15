#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QIODevice>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    QLocale lang;

    QFile flang(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/language");

    if (flang.open(QIODevice::ReadOnly))
    {
        lang = QLocale(QTextStream(&flang).readAll());
        flang.close();
    }
    else
        lang = QLocale::system();

    myappTranslator.load(lang, "brasilcov", "_", ":/lang");
    app.installTranslator(&myappTranslator);

    MainWindow mainwindow(&myappTranslator);
    mainwindow.show();

    return app.exec();
}