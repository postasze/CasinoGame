#include "generalsettingsform.h"
#include "ui_generalsettingsform.h"

GeneralSettingsForm::GeneralSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralSettingsForm)
{
    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();

    connect(ui->reelQuantitySpinBox, static_cast<void(QSpinBox::*)(int)> (&QSpinBox::valueChanged), this, &GeneralSettingsForm::reelQuantitySpinBoxValueChanged);
    connect(ui->symbolQuantitySpinBox, static_cast<void(QSpinBox::*)(int)> (&QSpinBox::valueChanged), this, &GeneralSettingsForm::symbolQuantitySpinBoxValueChanged);
    connect(ui->symbolsDisplayedVerticallyOnScreenQuantitySpinBox, static_cast<void(QSpinBox::*)(int)> (&QSpinBox::valueChanged), this, &GeneralSettingsForm::symbolsDisplayedVerticallyOnScreenQuantitySpinBoxValueChanged);

    currentReelQuantity = 1;
    currentSymbolQuantity = 1;
    currentSymbolsDisplayedVerticallyOnScreenQuantity = 1;
}

GeneralSettingsForm::~GeneralSettingsForm()
{
    delete ui;
}

void GeneralSettingsForm::reelQuantitySpinBoxValueChanged(int value)
{
    currentReelQuantity = value;
}

void GeneralSettingsForm::symbolQuantitySpinBoxValueChanged(int value)
{
    currentSymbolQuantity = value;
}

void GeneralSettingsForm::symbolsDisplayedVerticallyOnScreenQuantitySpinBoxValueChanged(int value)
{
    currentSymbolsDisplayedVerticallyOnScreenQuantity = value;
}

void GeneralSettingsForm::on_buttonBox_accepted()
{
    this->parentMdi->reelQuantity = currentReelQuantity;
    this->parentMdi->symbolQuantity = currentSymbolQuantity;
    this->parentMdi->symbolsDisplayedVerticallyOnScreenQuantity = currentSymbolsDisplayedVerticallyOnScreenQuantity;
    this->~GeneralSettingsForm();
    this->parentMdi->removeSubWindow();
}

void GeneralSettingsForm::on_buttonBox_rejected()
{
    this->~GeneralSettingsForm();
    this->parentMdi->removeSubWindow();
}
