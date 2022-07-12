#include "statsmenu.h"

StatsMenu::StatsMenu(BrCoVDataManager *datamgr, QWidget *parent) : QWidget(parent), ui(new Ui::StatsMenu)
{
    dmgr = datamgr;

    ui->setupUi(this);

    connect(ui->brazilRadio, &QRadioButton::clicked, this, &StatsMenu::triggerFetch);
    connect(ui->allCountriesRadio, &QRadioButton::clicked, this, &StatsMenu::triggerFetch);
    connect(ui->searchbox, &QLineEdit::textChanged, this, &StatsMenu::search);
}

bool StatsMenu::brazilSelected()
{
    return ui->brazilRadio->isChecked();
}

void StatsMenu::data(QVector<BrCoVDataItem> *data)
{
    updateUi(data, ui->searchbox->text());
}

void StatsMenu::triggerFetch()
{
    emit fetch();
}

void StatsMenu::search(QString text)
{
    QVector<BrCoVDataItem> data = dmgr->last();
    updateUi(&data, text);
}

void StatsMenu::updateUi(QVector<BrCoVDataItem> *data, QString search)
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
        if (search.isEmpty() || datai.name().toLower().contains(search.toLower()))
            ui->listArea->addWidget(new StatsItem(datai.name(), datai.suspects(), datai.cases(), datai.deaths()));
    }
}

StatsMenu::~StatsMenu()
{
    delete ui;
}