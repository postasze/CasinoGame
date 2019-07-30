#ifndef READINGFROMFILEFORM_H
#define READINGFROMFILEFORM_H

#include "mainwindow.h"
#include <fstream>
#include <string>

namespace Ui {
class ReadingFromFileForm;
}

class ReadingFromFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingFromFileForm(QWidget *parent = 0);
    ~ReadingFromFileForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ReadingFromFileForm *ui;
    MainWindow *parentMdi;

    bool readDataFromFile(string fileName);
};

#endif // READINGFROMFILEFORM_H
