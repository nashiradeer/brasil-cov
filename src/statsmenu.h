#ifndef __STATSMENU_H__
#define __STATSMENU_H__

#include "ui_statsmenu.h"
#include <QWidget>
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

private:
    Ui::StatsMenu *ui;
};

#endif