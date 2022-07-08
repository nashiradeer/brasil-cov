#include "statsmenu.h"

StatsMenu::StatsMenu(QWidget *parent) : QWidget(parent), ui(new Ui::StatsMenu)
{
    ui->setupUi(this);
    ui->listArea->setAlignment(Qt::AlignTop);
}

StatsMenu::~StatsMenu()
{
    delete ui;
}