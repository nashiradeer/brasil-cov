#ifndef __OPTIONSWINDOW_H__
#define __OPTIONSWINDOW_H__

#include "ui_optionswindow.h"
#include <QWidget>
#include <QTranslator>
#include <QComboBox>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>
#include <QIODevice>
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
    explicit OptionsWindow(QTranslator *translator, QWidget *parent = nullptr);
    virtual ~OptionsWindow();

protected slots:
    virtual void changeEvent(QEvent *event);

private slots:
    void closeWindow();
    void languageChange(int index);

private:
    Ui::OptionsWindow *ui;
    QShortcut *shortcut;
    QTranslator *transl;
    int lang2index(QString lang);
    QString index2lang(int index);
    QString index2translate(int index);
};

#endif