#ifndef REELSETTINGFORM_H
#define REELSETTINGFORM_H

#include "mainwindow.h"
#include <vector>

namespace Ui {
class ReelSettingForm;
}

class ReelSettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReelSettingForm(QWidget *parent = 0);
    ~ReelSettingForm();

    vector<vector<int>> *reels;
    //QGraphicsView *reelViewPointers[8];
    int currentSymbol;

private slots:
    void symbolComboBoxCurrentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ReelSettingForm *ui;
    MainWindow *parentMdi;
    QGraphicsScene *reelScenePointer;
    QGraphicsView *reelViewPointer;
};

#endif // REELSETTINGFORM_H
