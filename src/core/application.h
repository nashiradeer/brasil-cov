#ifndef _BRCOVAPPLICATION_H_
#define _BRCOVAPPLICATION_H_

#include <QApplication>
#include <QFile>
#include <QtGlobal>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>
#include <QTranslator>

namespace BrasilCoV {
    class BrCoVApplication;
}

class BrCoVApplication : public QObject
{
    Q_OBJECT

public:
    const static int SystemTheme = 0;
    const static int DarkTheme = 1;
    const static int LightTheme = 2;
    explicit BrCoVApplication(QApplication *app, QObject *parent = nullptr);
    virtual ~BrCoVApplication();
    void translate(QLocale lang);
    QLocale getLocale();
    int getTheme();
    void setTheme(int theme);
    bool isSystemLight();
    void saveSettings();
    void loadSettings();

private:
    int currentTheme;
    QLocale locale;
    QApplication *application;
    QTranslator *translator;
    void updateTheme(int theme);
};

#endif // _BRCOVAPPLICATION_H_
