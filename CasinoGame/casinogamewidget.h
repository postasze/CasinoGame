#ifndef CASINOGAMEWIDGET_H
#define CASINOGAMEWIDGET_H

#include <QWidget>
#include <vector>
#include <fstream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>

// uwaga reel_velocity * reelquantity powinno byc mniejsze rowne spin time
#define REEL_VELOCITY 30
#define REEL_ACCELERATION 1
#define REEL_ELEMENT_HEIGHT 70
#define SPIN_TIME 150
#define MINIMAL_BET 125
#define MAXIMAL_BET 1250
#define BET_SIZE 125

using namespace std;

namespace Ui {
class CasinoGameWidget;
}

class CasinoGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CasinoGameWidget(string fileName, QWidget *parent = 0);
    ~CasinoGameWidget();

protected:
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

private slots:
    void start();
    void pause();
    void spin();

private:
    vector<vector<QGraphicsPixmapItem*>> *reelItems;
    vector<QGraphicsView*> *reels;
    vector<vector<int>> *reelIndexes;
    vector<int> *spinIndexes;
    vector<vector<int>> *prizes;
    vector<vector<int>> *lines;
    vector<int> *reelSpeeds;
    vector<int> *reelMaxSpeeds;
    vector<QGraphicsLineItem*> *machineLineElements;
    vector<vector<QGraphicsLineItem*>> *reelLineElements;
    unsigned int reelQuantity;
    unsigned int symbolQuantity;
    unsigned int linesQuantity;
    unsigned int symbolsDisplayedVerticallyOnScreenQuantity;
    QGraphicsView *viewPointer;
    QGraphicsScene *scenePointer;
    QGraphicsView *viewPointer1;
    QGraphicsScene *scenePointer1;
    QGraphicsPixmapItem *machinePixmapItem;
    QGraphicsPixmapItem *spinButtonPixmapItem;
    QTimer timer;
    unsigned long currentSpinTime;
    bool gamePaused;
    QLabel *creditLabel;
    QLabel *betLabel;
    QLabel *winLabel;
    unsigned int currentCredit;
    unsigned int currentBet;
    unsigned int prize;

    void prizeCalculation();
    void drawLine(vector<int> *line);
    void clearLines();
    bool readDataFromFile(string fileName);
};

#endif // CASINOGAMEWIDGET_H
