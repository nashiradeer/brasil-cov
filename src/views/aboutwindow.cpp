#include "aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, &QShortcut::activated, this, &AboutWindow::closeWindow);
}

AboutWindow::~AboutWindow()
{
    delete shortcut;
    delete ui;
}

void AboutWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
}

void AboutWindow::closeWindow()
{
    close();
}