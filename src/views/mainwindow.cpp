#include "mainwindow.h"

MainWindow::MainWindow(QTranslator *translator, QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeWindow);
    connect(ui->actionReload, &QAction::triggered, this, &MainWindow::fetch);

    options = new OptionsWindow(translator);
    about = new AboutWindow();

    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptions);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAbout);

    netmgr = new BrCoVNetwork(this);

    statsmenu = new StatsMenu(netmgr);

    ui->main->addWidget(statsmenu);

    connect(netmgr, &BrCoVNetwork::finished, statsmenu, &StatsMenu::data);
    connect(statsmenu, &StatsMenu::loaded, this, &MainWindow::disableWaiting);
    connect(statsmenu, &StatsMenu::fetch, this, &MainWindow::fetch);

    fetch();
}

MainWindow::~MainWindow()
{
    delete netmgr;
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

void MainWindow::fetch()
{
    this->setCursor(Qt::WaitCursor);
    if (statsmenu->brazilSelected())
        netmgr->fetchStates();
    else
        netmgr->fetchCountries();
}

void MainWindow::openOptions()
{
    options->show();
}

void MainWindow::disableWaiting()
{
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::openAbout()
{
    about->show();
}

void MainWindow::closeWindow()
{
    close();
}
