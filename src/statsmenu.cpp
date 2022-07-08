#include "statsmenu.h"

StatsMenu::StatsMenu(QWidget *parent) : QWidget(parent), ui(new Ui::StatsMenu)
{
    ui->setupUi(this);
}

StatsMenu::~StatsMenu()
{
    delete ui;
}