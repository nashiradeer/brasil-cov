#ifndef __OPTIONSWINDOW_H__
#define __OPTIONSWINDOW_H__

#include "ui_optionswindow.h"
#include <QWidget>
#include <QShortcut>
#include <QKeySequence>

namespace BrasilCoV
{
    class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    virtual ~OptionsWindow();

private slots:
    void closeWindow();

private:
    Ui::OptionsWindow *ui;
    QShortcut *shortcut;
};

#endif