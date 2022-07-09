#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QThread>
#include "core.h"
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
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~MainWindow();

private slots:
    void openOptions();
    void openAbout();
    void closeWindow();
    void reloadRequested();
    void dataReceived();

signals:
    void reload(bool brazilOnly);
    void data(CoVDataManager *mgr);

private:
    Ui::MainWindow *ui;
    CoVDataManager *datamgr;
    CoVNetworkManager *netmgr;
    StatsMenu *statsmenu;
    OptionsWindow *options;
    AboutWindow *about;
    CoVNetworkThread *netthread;
};

#endif