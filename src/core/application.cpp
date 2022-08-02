#include "application.h"

BrCoVApplication::BrCoVApplication(QApplication *app, QObject *parent) : QObject(parent)
{
    application = app;
    translator = new QTranslator();

    loadSettings();

    application->installTranslator(translator);
}

BrCoVApplication::~BrCoVApplication()
{
    application->removeTranslator(translator);
    delete translator;
}

void BrCoVApplication::translate(QLocale lang) {
    locale = lang;
    translator->load(locale, "brasilcov", "_", ":/assets/lang");
}

QLocale BrCoVApplication::getLocale()
{
    return locale;
}

int BrCoVApplication::getTheme()
{
    return currentTheme;
}

void BrCoVApplication::setTheme(int theme)
{
    currentTheme = theme;

    int realTheme = BrCoVApplication::DarkTheme;
    switch (currentTheme)
    {
        case BrCoVApplication::SystemTheme:
            if (isSystemLight())
                realTheme = BrCoVApplication::LightTheme;
        break;
        case BrCoVApplication::LightTheme:
            realTheme = BrCoVApplication::LightTheme;
    }

    updateTheme(realTheme);
}

bool BrCoVApplication::isSystemLight()
{
#ifdef Q_OS_WIN
    QSettings winreg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    return winreg.value("AppsUseLightTheme", 0) != 0;
#else
    return false;
#endif
}

void BrCoVApplication::loadSettings()
{
    QSettings settings("Nashira Deer", "Brasil CoV");

    translate(settings.value("Application/Language", QLocale::system()).toLocale());
    setTheme(settings.value("Application/Theme", BrCoVApplication::SystemTheme).toInt());
}

void BrCoVApplication::saveSettings()
{
    QSettings settings("Nashira Deer", "Brasil CoV");

    settings.setValue("Application/Language", locale);
    settings.setValue("Application/Theme", currentTheme);
}

void BrCoVApplication::updateTheme(int theme)
{
    QFile qss;

    if (theme == BrCoVApplication::LightTheme)
        qss.setFileName(":/assets/style/light.css");
    else
        qss.setFileName(":/assets/style/night.css");

    if (qss.open(QIODevice::ReadOnly))
        application->setStyleSheet(QTextStream(&qss).readAll());
}
