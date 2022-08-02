#include <QApplication>
#include <QFontDatabase>
#include "core/application.h"
#include "views/mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/assets/fonts/NotoSansDisplay-Medium.ttf");

    BrCoVApplication brasilcov(&app);

    MainWindow mainwindow(&brasilcov);
    mainwindow.show();

    return app.exec();
}
