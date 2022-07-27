#include "application.h"

BrCoVApplication::BrCoVApplication(QApplication *app, QObject *parent) : QObject(parent)
{
    application = app;

}

bool BrCoVApplication::loadSettings()
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/config.ini");
}
