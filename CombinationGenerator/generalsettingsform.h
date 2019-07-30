#ifndef GENERALSETTINGSFORM_H
#define GENERALSETTINGSFORM_H

#include "mainwindow.h"

namespace Ui {
class GeneralSettingsForm;
}

class GeneralSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralSettingsForm(QWidget *parent = 0);
    ~GeneralSettingsForm();

private slots:
    void reelQuantitySpinBoxValueChanged(int value);
    void symbolQuantitySpinBoxValueChanged(int value);
    void symbolsDisplayedVerticallyOnScreenQuantitySpinBoxValueChanged(int value);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GeneralSettingsForm *ui;
    MainWindow *parentMdi;
    quint16 currentSymbolQuantity;
    quint16 currentReelQuantity;
    quint16 currentSymbolsDisplayedVerticallyOnScreenQuantity;
};

#endif // GENERALSETTINGSFORM_H
