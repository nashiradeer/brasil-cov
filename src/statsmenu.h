#ifndef __STATSMENU_H__
#define __STATSMENU_H__

#include "ui_statsmenu.h"
#include <QWidget>
#include "core.h"
#include "statsitem.h"

namespace BrasilCoV
{
    class StatsMenu;
}

class StatsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StatsMenu(QWidget *parent = nullptr);
    virtual ~StatsMenu();
    bool brazilSelected();

signals:
    void fetch();

public slots:
    void data(QVector<BrCoVDataItem> *data);

private slots:
    void triggerFetch();

private:
    Ui::StatsMenu *ui;
};

#endif