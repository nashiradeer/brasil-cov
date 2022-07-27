#include "statsmenu.h"

StatsMenu::StatsMenu(BrCoVDataManager *datamgr, QWidget *parent) : QWidget(parent), ui(new Ui::StatsMenu)
{
    dmgr = datamgr;

    ui->setupUi(this);

    connect(ui->brazilRadio, &QRadioButton::clicked, this, &StatsMenu::triggerFetch);
    connect(ui->allCountriesRadio, &QRadioButton::clicked, this, &StatsMenu::triggerFetch);
    connect(ui->searchbox, &QLineEdit::textChanged, this, &StatsMenu::search);
}

void StatsMenu::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        updateUi(dmgr->last(), ui->searchbox->text());
    }
}

bool StatsMenu::brazilSelected()
{
    return ui->brazilRadio->isChecked();
}

void StatsMenu::data()
{
    updateUi(dmgr->last(), ui->searchbox->text());
}

void StatsMenu::triggerFetch()
{
    emit fetch();
}

void StatsMenu::search(QString text)
{
    updateUi(dmgr->last(), text);
}

void StatsMenu::updateUi(QVector<BrCoVDataItem> data, QString search)
{
    while (!ui->listArea->layout()->isEmpty())
    {
        QLayoutItem *item = ui->listArea->layout()->takeAt(0);
        ui->listArea->layout()->removeItem(item);
        delete item->widget();
        delete item->layout();
        delete item;
    }

    for (int i = 0; i < data.size(); i++)
    {
        BrCoVDataItem datai = data.operator[](i);
        if (search.isEmpty() || datai.name().toLower().contains(search.toLower()))
            ui->listArea->layout()->addWidget(new StatsItem(datai.name(), datai.suspects(), datai.cases(), datai.deaths()));
    }
}

StatsMenu::~StatsMenu()
{
    while (!ui->listArea->layout()->isEmpty())
    {
        QLayoutItem *item = ui->listArea->layout()->takeAt(0);
        ui->listArea->layout()->removeItem(item);
        delete item->widget();
        delete item->layout();
        delete item;
    }

    delete ui;
}
