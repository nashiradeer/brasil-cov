#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeWindow);

    options = new OptionsWindow();
    about = new AboutWindow();

    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptions);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::openAbout);

    statsmenu = new StatsMenu();

    ui->main->addWidget(statsmenu);
}

MainWindow::~MainWindow()
{
    delete options;
    delete about;
    delete statsmenu;
    delete ui;
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