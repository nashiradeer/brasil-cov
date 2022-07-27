#ifndef __ABOUTWINDOW_H__
#define __ABOUTWINDOW_H__

#include "ui_aboutwindow.h"
#include <QWidget>
#include <QShortcut>
#include <QKeySequence>

namespace BrasilCoV
{
    class AboutWindow;
}

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    virtual ~AboutWindow();

protected slots:
    virtual void changeEvent(QEvent *event);

private slots:
    void closeWindow();

private:
    Ui::AboutWindow *ui;
    QShortcut *shortcut;
};

#endif