#include "optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, &QShortcut::activated, this, &OptionsWindow::closeWindow);
}

OptionsWindow::~OptionsWindow()
{
    delete shortcut;
    delete ui;
}

void OptionsWindow::closeWindow()
{
    close();
}