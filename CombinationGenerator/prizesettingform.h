#ifndef PRIZESETTINGFORM_H
#define PRIZESETTINGFORM_H

#include "mainwindow.h"
#include <vector>

namespace Ui {
class PrizeSettingForm;
}

class PrizeSettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit PrizeSettingForm(QWidget *parent = 0);
    ~PrizeSettingForm();

private slots:
    void symbolComboBoxCurrentIndexChanged(int index);
    void multiplierComboBoxCurrentIndexChanged(int index);
    void prizeSpinBoxValueChanged(int value);
    void addPrizeButtonClicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PrizeSettingForm *ui;
    MainWindow *parentMdi;
    int currentSymbolIndex;
    int currentMultiplierIndex;
    int currentPrize;
    vector<vector<int>> *prizes;
};

#endif // PRIZESETTINGFORM_H
