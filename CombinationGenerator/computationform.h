#ifndef COMPUTATIONFORM_H
#define COMPUTATIONFORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class ComputationForm;
}

class ComputationForm : public QWidget
{
    Q_OBJECT

public:
    explicit ComputationForm(QWidget *parent = 0);
    ~ComputationForm();

private slots:
    void computationButtonClicked();
    void acceptButtonClicked();
    void cancelButtonClicked();

private:
    MainWindow *parentMdi;
    Ui::ComputationForm *ui;
    QString computationResultString;
    vector<int> *symbolCountsOnLine;
    vector<int> *reelIndexes;
    bool allCombinationsComputed;
    int currentSymbol;
    double prizeSum;
    double combinationsQuantity;
    double combinationsComputed;
    double noPrizeCombinationsQuantity;
};

#endif // COMPUTATIONFORM_H
