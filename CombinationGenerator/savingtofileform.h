#ifndef SAVINGTOFILEFORM_H
#define SAVINGTOFILEFORM_H

#include "mainwindow.h"
#include <fstream>

namespace Ui {
class SavingToFileForm;
}

class SavingToFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit SavingToFileForm(QWidget *parent = 0);
    ~SavingToFileForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SavingToFileForm *ui;
    MainWindow *parentMdi;

    bool saveDataToFile(string fileName);
};

#endif // SAVINGTOFILEFORM_H
