#ifndef RESULTDISPLAYFORM_H
#define RESULTDISPLAYFORM_H

#include "mainwindow.h"

namespace Ui {
class ResultDisplayForm;
}

class ResultDisplayForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultDisplayForm(QWidget *parent = 0);
    ~ResultDisplayForm();

private:
    Ui::ResultDisplayForm *ui;
    MainWindow *parentMdi;
};

#endif // RESULTDISPLAYFORM_H
