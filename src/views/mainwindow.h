#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QThread>
#include <QTranslator>
#include "../core/application.h"
#include "../core/network.h"
#include "statsmenu.h"
#include "optionswindow.h"
#include "aboutwindow.h"

namespace BrasilCoV
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(BrCoVApplication *app, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~MainWindow();

protected slots:
    virtual void changeEvent(QEvent *event);

private slots:
    void openOptions();
    void openAbout();
    void closeWindow();
    void fetch();
    void disableWaiting();

signals:
    void reload(bool brazilOnly);

private:
    Ui::MainWindow *ui;
    BrCoVNetwork *netmgr;
    StatsMenu *statsmenu;
    OptionsWindow *options;
    AboutWindow *about;
};

#endif
