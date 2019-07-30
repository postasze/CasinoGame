#include "prizesettingform.h"
#include "ui_prizesettingform.h"
#include <iostream>

PrizeSettingForm::PrizeSettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrizeSettingForm)
{
    QString comboBoxItem;

    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();

    prizes = new vector<vector<int>>();

    for(unsigned int i = 0; i < parentMdi->symbolQuantity; i++)
    {
        prizes->push_back(*(new vector<int>()));
        for(unsigned int j = 0; j < parentMdi->reelQuantity; j++)
            prizes->at(i).push_back(0);

        comboBoxItem += "Symbol " + QString::number(i+1);
        ui->symbolComboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
    ui->symbolComboBox->setCurrentIndex(0);
    ui->prizeSpinBox->setValue(0);

    currentSymbolIndex = 0;
    currentMultiplierIndex = 1;

    connect(ui->symbolComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &PrizeSettingForm::symbolComboBoxCurrentIndexChanged);
    connect(ui->multiplierComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &PrizeSettingForm::multiplierComboBoxCurrentIndexChanged);
    connect(ui->prizeSpinBox, static_cast<void(QSpinBox::*)(int)> (&QSpinBox::valueChanged), this, &PrizeSettingForm::prizeSpinBoxValueChanged);
    connect(ui->addPrizeButton, &QPushButton::clicked, this, &PrizeSettingForm::addPrizeButtonClicked);

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
    {
        comboBoxItem += QString::number(i+1);
        ui->multiplierComboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
    ui->multiplierComboBox->setCurrentIndex(0);

    if(parentMdi->prizes != nullptr)
        *this->prizes = *parentMdi->prizes; // kopia
}

PrizeSettingForm::~PrizeSettingForm()
{
    delete ui;
}

void PrizeSettingForm::symbolComboBoxCurrentIndexChanged(int index)
{
    currentSymbolIndex = index;
    ui->multiplierComboBox->setCurrentIndex(0);
    ui->prizeSpinBox->setValue(prizes->at(currentSymbolIndex).at(currentMultiplierIndex));
}

void PrizeSettingForm::multiplierComboBoxCurrentIndexChanged(int index)
{
    currentMultiplierIndex = index;
    ui->prizeSpinBox->setValue(prizes->at(currentSymbolIndex).at(currentMultiplierIndex));
}

void PrizeSettingForm::prizeSpinBoxValueChanged(int value)
{
    currentPrize = value;
}

void PrizeSettingForm::addPrizeButtonClicked()
{
    prizes->at(currentSymbolIndex).at(currentMultiplierIndex) = currentPrize;
    ui->prizeSpinBox->clear();
}

void PrizeSettingForm::on_buttonBox_accepted()
{
    if(parentMdi->prizes != nullptr)
        free(parentMdi->prizes);
    parentMdi->prizes = this->prizes;
    this->~PrizeSettingForm();
    this->parentMdi->removeSubWindow();
}

void PrizeSettingForm::on_buttonBox_rejected()
{
    this->~PrizeSettingForm();
    this->parentMdi->removeSubWindow();
}
