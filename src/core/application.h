#ifndef _BRCOVAPPLICATION_H_
#define _BRCOVAPPLICATION_H_

#include <QSettings>
#include <QStandardPaths>
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
    void translate(QString lang);
    void setTheme(int theme);
    int getTheme();
    void updateSystemTheme();
    bool isSystemLight();
    bool saveSettings();
    bool loadSettings();

private:
    QApplication *application;
    QSettings settings;
    QTranslator translator;
    void updateTheme(int theme);

};

#endif // _BRCOVAPPLICATION_H_
