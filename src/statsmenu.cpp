#include "statsmenu.h"

StatsMenu::StatsMenu(QWidget *parent) : QWidget(parent), ui(new Ui::StatsMenu)
{
    ui->setupUi(this);
}

bool StatsMenu::brazilSelected()
{
    return ui->brazilRadio->isChecked();
}

void StatsMenu::data(QVector<BrCoVDataItem> *data)
{
    QLayoutItem *item;
    while ((item = ui->listArea->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < data->size(); i++)
    {
        BrCoVDataItem datai = data->operator[](i);
        ui->listArea->addWidget(new StatsItem(datai.name(), datai.suspects(), datai.cases(), datai.deaths()));
    }
}

StatsMenu::~StatsMenu()
{
    delete ui;
}