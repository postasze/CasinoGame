#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QSpinBox>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void removeSubWindow();
    vector<vector<int>> *reels;
    vector<vector<int>> *prizes;
    vector<vector<int>> *lines;
    unsigned int reelQuantity;
    unsigned int symbolQuantity;
    unsigned int linesQuantity;
    unsigned int symbolsDisplayedVerticallyOnScreenQuantity;
    QString computationResultString;

private slots:
    void generalSettingsFormOpened();
    void savingToFileFormOpened();
    void lineSettingFormOpened();
    void prizeSettingFormOpened();
    void reelSettingFormOpened();
    void resultDisplayFormOpened();
    void readingFromFileFormOpened();
    void computationFormOpened();

private:
    Ui::MainWindow *ui;
    void loadSubWindow(QWidget *widget);
};

#endif // MAINWINDOW_H
