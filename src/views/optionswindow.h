#ifndef __OPTIONSWINDOW_H__
#define __OPTIONSWINDOW_H__

#include "ui_optionswindow.h"
#include <QWidget>
#include <QComboBox>
#include <QShortcut>
#include <QKeySequence>
#include "../core/application.h"

namespace BrasilCoV
{
    class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(BrCoVApplication *app, QWidget *parent = nullptr);
    virtual ~OptionsWindow();

protected slots:
    virtual void changeEvent(QEvent *event);

private slots:
    void closeWindow();
    void languageChange(int index);

private:
    Ui::OptionsWindow *ui;
    QShortcut *shortcut;
    BrCoVApplication *application;
    QLocale langIndex(int index);
    void updateLangIndex();
    void updateThemeSelection();
    void selectSystemTheme();
    void selectDarkTheme();
    void selectLightTheme();
};

#endif
