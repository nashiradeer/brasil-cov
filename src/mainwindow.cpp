#include "mainwindow.h"

MainWindow::MainWindow(QTranslator *translator, QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeWindow);
    connect(ui->actionReload, &QAction::triggered, this, &MainWindow::reloadRequested);

    options = new OptionsWindow(translator);
    about = new AboutWindow();

    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptions);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAbout);

    datamgr = new BrCoVDataManager(this);

    statsmenu = new StatsMenu(datamgr);

    ui->main->addWidget(statsmenu);

    connect(datamgr, &BrCoVDataManager::parsed, statsmenu, &StatsMenu::data);
    connect(statsmenu, &StatsMenu::fetch, this, &MainWindow::reloadRequested);

    if (statsmenu->brazilSelected())
    {
        datamgr->fetchStates();
    }
    else
    {
        datamgr->fetchCountries();
    }
}

MainWindow::~MainWindow()
{
    delete datamgr;
    delete options;
    delete about;
    delete statsmenu;
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
}

void MainWindow::reloadRequested()
{
    if (statsmenu->brazilSelected())
    {
        datamgr->fetchStates();
    }
    else
    {
        datamgr->fetchCountries();
    }
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