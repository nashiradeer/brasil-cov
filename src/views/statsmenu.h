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
    explicit StatsMenu(BrCoVDataManager *datamgr, QWidget *parent = nullptr);
    virtual ~StatsMenu();
    bool brazilSelected();

signals:
    void fetch();

public slots:
    void data();

protected slots:
    virtual void changeEvent(QEvent *event);

private slots:
    void triggerFetch();
    void search(QString text);

private:
    void updateUi(QVector<BrCoVDataItem> data, QString search = "");
    Ui::StatsMenu *ui;
    BrCoVDataManager *dmgr;
};

#endif