#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    datamgr = new CoVDataManager(this);
    connect(datamgr, &CoVDataManager::updated, this, &MainWindow::dataReceived);

    netmgr = new CoVNetworkManager(datamgr, this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeWindow);
    connect(ui->actionReload, &QAction::triggered, this, &MainWindow::reloadRequested);

    options = new OptionsWindow();
    about = new AboutWindow();

    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptions);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAbout);

    statsmenu = new StatsMenu();
    connect(this, &MainWindow::data, statsmenu, &StatsMenu::data);

    netthread = new CoVNetworkThread(netmgr, statsmenu->brazilSelected(), this);
    netthread->start();

    ui->main->addWidget(statsmenu);
}

MainWindow::~MainWindow()
{
    netthread->quit();
    netthread->wait();
    delete netthread;
    delete netmgr;
    delete datamgr;
    delete options;
    delete about;
    delete statsmenu;
    delete ui;
}

void MainWindow::reloadRequested()
{
    netthread->setBrazil(statsmenu->brazilSelected());
    netthread->start();
}

void MainWindow::dataReceived()
{
    emit data(datamgr);
}

void MainWindow::openOptions()
{
    options->show();
}

void MainWindow::openAbout()
{
    about->show();
}

void MainWindow::closeWindow()
{
    close();
}