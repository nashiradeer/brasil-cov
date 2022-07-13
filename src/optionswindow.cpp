#include "optionswindow.h"

OptionsWindow::OptionsWindow(QTranslator *translator, QWidget *parent) : QWidget(parent), ui(new Ui::OptionsWindow)
{
    transl = translator;

    ui->setupUi(this);

    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, &QShortcut::activated, this, &OptionsWindow::closeWindow);

    for (int i = 0; i <= 1; i++)
        ui->language->addItem(index2translate(i), QLocale(index2lang(i)));

    ui->language->setCurrentIndex(lang2index(translator->language()));

    connect(ui->language, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWindow::languageChange);
}

OptionsWindow::~OptionsWindow()
{
    delete shortcut;
    delete ui;
}

void OptionsWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);

        for (int i = 0; i < ui->language->count(); i++)
            ui->language->setItemText(i, index2translate(i));

        ui->language->setCurrentIndex(lang2index(transl->language()));
    }
}

void OptionsWindow::languageChange(int index)
{
    transl->load(ui->language->itemData(index).toLocale(), "brasilcov", "_", ":/lang");

    if (QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)))
    {
        QFile flang(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/language");

        if (flang.open(QIODevice::WriteOnly))
        {
            QTextStream(&flang) << index2lang(index);
            flang.close();
        }
    }
}

int OptionsWindow::lang2index(QString lang)
{
    if (lang.startsWith("pt"))
        return 1;
    else
        return 0;
}

QString OptionsWindow::index2lang(int index)
{
    switch (index)
    {
    case 1:
        return "pt";
    default:
        return "en";
    }
}

QString OptionsWindow::index2translate(int index)
{
    switch (index)
    {
    case 1:
        return tr("Portugues");
    default:
        return tr("English");
    }
}

void OptionsWindow::closeWindow()
{
    close();
}