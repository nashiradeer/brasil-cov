#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statsmenu = new StatsMenu();

    ui->main->addWidget(statsmenu);
}

MainWindow::~MainWindow()
{
    delete statsmenu;
    delete ui;
}