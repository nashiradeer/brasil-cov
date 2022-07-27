#include "statsitem.h"

StatsItem::StatsItem(QString title, quint32 suspects, quint32 cases, quint32 deaths, QWidget *parent) : QWidget(parent), ui(new Ui::StatsItem)
{
    ui->setupUi(this);

    ui->supectsValue->setText(QString::number(suspects));
    ui->casesValue->setText(QString::number(cases));
    ui->deathsValue->setText(QString::number(deaths));
    ui->title->setText(title);
}

StatsItem::~StatsItem()
{
    delete ui;
}