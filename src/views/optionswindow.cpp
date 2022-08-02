#include "optionswindow.h"

OptionsWindow::OptionsWindow(BrCoVApplication *app, QWidget *parent) : QWidget(parent), ui(new Ui::OptionsWindow)
{
    application = app;

    ui->setupUi(this);

    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(shortcut, &QShortcut::activated, this, &OptionsWindow::closeWindow);

    for (int i = 0; i <= 1; i++)
    {
        QLocale locale = langIndex(i);
        ui->language->addItem(QLocale::languageToString(locale.language()), locale);
    }

    updateLangIndex();
    updateThemeSelection();

    connect(ui->language, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OptionsWindow::languageChange);

    connect(ui->systemTheme, &QRadioButton::clicked, this, &OptionsWindow::selectSystemTheme);
    connect(ui->nighTheme, &QRadioButton::clicked, this, &OptionsWindow::selectDarkTheme);
    connect(ui->lightTheme, &QRadioButton::clicked, this, &OptionsWindow::selectLightTheme);
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
        updateLangIndex();
    }
}

void OptionsWindow::updateLangIndex()
{
    for (int i = 0; i < ui->language->count(); i++)
    {
        if (ui->language->itemData(i).toLocale().language() == application->getLocale().language())
        {
            ui->language->setCurrentIndex(i);
            return;
        }
    }

    ui->language->setCurrentIndex(0);
}

void OptionsWindow::languageChange(int index)
{
    application->translate(langIndex(index));
    application->saveSettings();
}

QLocale OptionsWindow::langIndex(int index)
{
    switch (index)
    {
    case 1:
        return QLocale::Portuguese;
    default:
        return QLocale::English;
    }
}

void OptionsWindow::updateThemeSelection()
{
    int theme = application->getTheme();

    switch (theme)
    {
    case BrCoVApplication::DarkTheme:
        ui->nighTheme->setChecked(true);
        break;
    case BrCoVApplication::LightTheme:
        ui->lightTheme->setChecked(true);
        break;
    default:
        ui->systemTheme->setChecked(true);
        break;
    }
}

void OptionsWindow::selectSystemTheme()
{
    application->setTheme(BrCoVApplication::SystemTheme);
    application->saveSettings();
}

void OptionsWindow::selectDarkTheme()
{
    application->setTheme(BrCoVApplication::DarkTheme);
    application->saveSettings();
}

void OptionsWindow::selectLightTheme()
{
    application->setTheme(BrCoVApplication::LightTheme);
    application->saveSettings();
}

void OptionsWindow::closeWindow()
{
    close();
}
