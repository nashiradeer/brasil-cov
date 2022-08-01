#ifndef __STATSITEM_H__
#define __STATSITEM_H__

#include "ui_statsitem.h"
#include <QWidget>

namespace BrasilCoV
{
    class StatsItem;
}

class StatsItem : public QWidget
{
    Q_OBJECT

public:
    explicit StatsItem(QString title, quint32 suspects, quint32 cases, quint32 deaths, QWidget *parent = nullptr);
    virtual ~StatsItem();

private:
    Ui::StatsItem *ui;
};

#endif