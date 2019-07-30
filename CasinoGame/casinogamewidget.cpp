#include "casinogamewidget.h"
#include <iostream>

using namespace std;

CasinoGameWidget::CasinoGameWidget(string fileName, QWidget *parent) :
    QWidget(parent)
{
    QGraphicsPixmapItem *pixmapItemPointer;
    unsigned int shift;;

    reelIndexes = new vector<vector<int>>();
    spinIndexes = new vector<int>();
    reelItems = new vector<vector<QGraphicsPixmapItem*>>();
    reels = new vector<QGraphicsView*>();
    reelSpeeds = new vector<int>();
    reelMaxSpeeds = new vector<int>();
    prizes = new vector<vector<int>>();
    lines = new vector<vector<int>>();
    reelLineElements = new vector<vector<QGraphicsLineItem*>>();
    machineLineElements = new vector<QGraphicsLineItem*>();

    readDataFromFile(fileName);

    gamePaused = true;
    currentSpinTime = 0;
    qsrand((uint)QTime::currentTime().msec());
    currentBet = 125;
    currentCredit = 10000;

    scenePointer = new QGraphicsScene(this);
    //scenePointer->setItemIndexMethod(QGraphicsScene::NoIndex);
    viewPointer = new QGraphicsView(scenePointer, this);

    //scenePointer->setSceneRect(0, 0, 2885, 2490);
    viewPointer->setFixedSize(885, 490);
    viewPointer->setSceneRect(0, 0, 885, 490);
    viewPointer->setBackgroundBrush(QBrush(QColor(240, 220, 155)));
    viewPointer->move(0, 0);
    viewPointer->show();
    //scrollAreaPointer->setWidget(reelViewPointer);
    viewPointer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewPointer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    machinePixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/machines/machine21.png"));
    viewPointer->scene()->addItem(machinePixmapItem);

    creditLabel = new QLabel(this);
    betLabel = new QLabel(this);
    winLabel = new QLabel(this);

    creditLabel->setText("10000       ");
    betLabel->setText("125      ");
    winLabel->setText("0      ");

    creditLabel->setStyleSheet("QLabel { background-color : black; color : orange; }");
    betLabel->setStyleSheet("QLabel { background-color : black; color : orange; }");
    winLabel->setStyleSheet("QLabel { background-color : black; color : orange; }");

    creditLabel->move(150, 330);
    betLabel->move(290, 330);
    winLabel->move(710, 330);


    for(unsigned int i = 0; i < reelQuantity; i++)
    {
        reelItems->push_back(*(new vector<QGraphicsPixmapItem*>()));
        reelSpeeds->push_back(0);
        reelMaxSpeeds->push_back((i+1)*REEL_VELOCITY);
        spinIndexes->push_back(0);
        reelLineElements->push_back(*(new vector<QGraphicsLineItem*>));

        reels->push_back(new QGraphicsView(new QGraphicsScene(this), this));
        reels->at(i)->setSceneRect(0, 0, 115, 210);
        reels->at(i)->setBackgroundBrush(QBrush(QColor(240, 220, 155, 0)));
        reels->at(i)->move(115*(i+1) + 20*i, 85);
        reels->at(i)->show();
        pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/machines/reel.png"));
        reels->at(i)->scene()->addItem(pixmapItemPointer);
        shift = qrand() % reelIndexes->at(i).size();

        for(unsigned int j = 0; j < reelIndexes->at(i).size(); j++)
        {
            switch(reelIndexes->at(i).at(j))
            {
            case 1:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/2win.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 2:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/bananas.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 3:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/bar.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 4:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/bell.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 5:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/cherry.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 6:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/coin.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 7:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/corns.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 8:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/diamond.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 9:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/dice.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 10:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/four_leaf_clover.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 11:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/grapefruits.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 12:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/horsehoe.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 13:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/lemons.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 14:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/orange.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 15:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/plum.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 16:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/seven.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 17:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/silver_coin.png"));
                pixmapItemPointer->setScale(1.5);
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            case 18:
                pixmapItemPointer = new QGraphicsPixmapItem(QPixmap(":/images/symbols/najfajniejsze/transparent/strawberries.png"));
                pixmapItemPointer->setX(20);
                pixmapItemPointer->setY(REEL_ELEMENT_HEIGHT * ((j + shift) % reelIndexes->at(i).size()));
                break;
            }
            reelItems->at(i).push_back(pixmapItemPointer);
            reels->at(i)->scene()->addItem(pixmapItemPointer);

        }
    }
    timer.start(1000/33);
}

CasinoGameWidget::~CasinoGameWidget()
{

}

void CasinoGameWidget::start()
{
    currentSpinTime = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(spin()));
    gamePaused = false;
}

void CasinoGameWidget::pause()
{
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(spin()));
    gamePaused = true;
}

void CasinoGameWidget::spin()
{
    unsigned int remainder = 0;
    bool reelsStopped = true;

    if(currentSpinTime < SPIN_TIME)
    {
        for(unsigned int i = 0; i < reelQuantity; i++)
        {
            if(reelSpeeds->at(i) < reelMaxSpeeds->at(i))
                reelSpeeds->at(i) += REEL_ACCELERATION;
            for(unsigned int j = 0; j < reelItems->at(i).size(); j++)
                reelItems->at(i).at(j)->setY(((int)reelItems->at(i).at(j)->y() + reelSpeeds->at(i)) % (reelItems->at(i).size() * REEL_ELEMENT_HEIGHT));
        }
        currentSpinTime++;
    }
    else
    {
        for(unsigned int i = 0; i < reelQuantity; i++)
        {
            if(reelSpeeds->at(i) > 0)
            {
                reelsStopped = false;
                reelSpeeds->at(i) -= REEL_ACCELERATION;
                for(unsigned int j = 0; j < reelItems->at(i).size(); j++)
                    reelItems->at(i).at(j)->setY(((int)reelItems->at(i).at(j)->y() + reelSpeeds->at(i)) % (reelItems->at(i).size() * REEL_ELEMENT_HEIGHT));
            }
            else // reelSpeeds->at(i) == 0
            {
                remainder = (int)reelItems->at(i).at(0)->y() % REEL_ELEMENT_HEIGHT;
                for(unsigned int j = 0; j < reelItems->at(i).size(); j++)
                    reelItems->at(i).at(j)->setY((int)reelItems->at(i).at(j)->y() - remainder);
            }
        }
        if(reelsStopped)
        {
            for(unsigned int i = 0; i < reelQuantity; i++)
            {
                for(unsigned int j = 0; j < reelItems->at(i).size(); j++)
                {
                    if(reelItems->at(i).at(j)->y() == 0)
                    {
                        spinIndexes->at(i) = j;
                        break;
                    }
                }
            }
            prizeCalculation();
            pause();
        }
    }
}

void CasinoGameWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    if(gamePaused)
    {
        switch(keyEvent->key())
        {
        case Qt::Key_Space:
            clearLines();
            currentCredit -= currentBet;
            creditLabel->setText(QString::number(currentCredit));
            start();
            break;
        default:
            break;
        }
    }
    else
    {

    }
}

void CasinoGameWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if(gamePaused)
    {
        switch(keyEvent->key())
        {
        case Qt::Key_A:
            if(currentBet > MINIMAL_BET)
            {
                currentBet -= BET_SIZE;
                betLabel->setText(QString::number(currentBet));
            }
            break;
        case Qt::Key_D:
            if(currentBet < MAXIMAL_BET)
            {
                currentBet += BET_SIZE;
                betLabel->setText(QString::number(currentBet));
            }
            break;
        default:
            break;
        }
    }
    else
    {

    }
}

void CasinoGameWidget::prizeCalculation()
{
    unsigned int currentSymbol;
    vector<int> *symbolCountsOnLine = new vector<int>();
    prize = 0;
    bool winningLine;

    for(unsigned int i = 0; i < symbolQuantity; i++)
        symbolCountsOnLine->push_back(0);

    for(unsigned int i = 0; i < lines->size(); i++) // liczba linii dowolna
    {
        winningLine = false;
        for(unsigned int j = 0; j < lines->at(i).size(); j++) // tyle co reelQuantity
        {
            currentSymbol = reelIndexes->at(j).at((spinIndexes->at(j) + lines->at(i).at(j)) % reelIndexes->at(j).size());
            currentSymbol--;
            symbolCountsOnLine->at(currentSymbol) += 1;
        }

        for(unsigned int j = 0; j < symbolCountsOnLine->size(); j++) // tyle co symbolQuantity
        {
            if(symbolCountsOnLine->at(j) > 0 && (prizes->at(j).at(symbolCountsOnLine->at(j)-1) > 0))
            {
                prize += prizes->at(j).at(symbolCountsOnLine->at(j)-1);
                winningLine = true;
            }
        }
        for(unsigned int j = 0; j < symbolCountsOnLine->size(); j++) // tyle co symbolQuantity
            symbolCountsOnLine->at(j) = 0; // czyszczenie wystapien symboli

        if(winningLine)
        {
            drawLine(&lines->at(i));
        }
    }
    prize *= currentBet / lines->size();
    winLabel->setText(QString::number(prize));
    currentCredit += prize;
    creditLabel->setText(QString::number(currentCredit));
}

void CasinoGameWidget::drawLine(vector<int> *line)
{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
    QGraphicsLineItem *lineElementPointer;
    unsigned short randomRed = qrand() % 256;
    unsigned short randomGreen = qrand() % 256;
    unsigned short randomBlue = qrand() % 256;
    int offset = 10 + 3*machineLineElements->size()/(reelQuantity-1);
    unsigned short alpha = 150;

    for(unsigned int i = 0; i < reelQuantity; i++)
    {
        if(i == 0)
        {
            a1 = -20 - 115.0/2.0;
            b1 = line->at(i) * REEL_ELEMENT_HEIGHT + offset;
            x1 = reels->at(i)->x() + 115.0/2.0;
            y1 = reels->at(i)->y() + line->at(i) * REEL_ELEMENT_HEIGHT + offset;
            continue;
        }
        if(i == (reelQuantity - 1))
        {
            a2 = 115.0/2.0;
            b2 = line->at(i) * REEL_ELEMENT_HEIGHT + offset;
            x2 = reels->at(i)->x() + 115.0/2.0;
            y2 = reels->at(i)->y() + line->at(i) * REEL_ELEMENT_HEIGHT + offset;

            lineElementPointer = new QGraphicsLineItem(x1, y1, x2, y2);
            lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
            viewPointer->scene()->addItem(lineElementPointer);
            machineLineElements->push_back(lineElementPointer);

            lineElementPointer = new QGraphicsLineItem(a1, b1, a2, b2);
            lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
            reels->at(i)->scene()->addItem(lineElementPointer);
            reelLineElements->at(i).push_back(lineElementPointer);

            lineElementPointer = new QGraphicsLineItem(115.0/2.0, line->at(i-1) * REEL_ELEMENT_HEIGHT + offset, 115 + 20 + 115.0/2.0, line->at(i) * REEL_ELEMENT_HEIGHT + offset);
            lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
            reels->at(i-1)->scene()->addItem(lineElementPointer);
            reelLineElements->at(i-1).push_back(lineElementPointer);

            continue;
        }
        a2 = 115.0/2.0;
        b2 = line->at(i) * REEL_ELEMENT_HEIGHT + offset;
        x2 = reels->at(i)->x() + 115.0/2.0;
        y2 = reels->at(i)->y() + line->at(i) * REEL_ELEMENT_HEIGHT + offset;

        lineElementPointer = new QGraphicsLineItem(x1, y1, x2, y2);
        lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
        viewPointer->scene()->addItem(lineElementPointer);
        machineLineElements->push_back(lineElementPointer);

        lineElementPointer = new QGraphicsLineItem(a1, b1, a2, b2);
        lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
        reels->at(i)->scene()->addItem(lineElementPointer);
        reelLineElements->at(i).push_back(lineElementPointer);

        lineElementPointer = new QGraphicsLineItem(115.0/2.0, line->at(i-1) * REEL_ELEMENT_HEIGHT + offset, 115 + 20 + 115.0/2.0, line->at(i) * REEL_ELEMENT_HEIGHT + offset);
        lineElementPointer->setPen(QPen(QBrush(QColor(randomRed, randomGreen, randomBlue, alpha)), 3));
        reels->at(i-1)->scene()->addItem(lineElementPointer);
        reelLineElements->at(i-1).push_back(lineElementPointer);

        a1 = -20 - 115.0/2.0;
        b1 = line->at(i) * REEL_ELEMENT_HEIGHT + offset;
        x1 = reels->at(i)->x() + 115.0/2.0;
        y1 = reels->at(i)->y() + line->at(i) * REEL_ELEMENT_HEIGHT + offset;
    }
}

void CasinoGameWidget::clearLines()
{
    for(unsigned int i = 0; i < machineLineElements->size(); i++)
    {
        viewPointer->scene()->removeItem(machineLineElements->at(i));
        machineLineElements->at(i)->~QGraphicsLineItem();
    }
    machineLineElements->clear();

    for(unsigned int i = 0; i < reelQuantity; i++)
    {
        for(unsigned int j = 0; j < reelLineElements->at(i).size(); j++)
        {
            reels->at(i)->scene()->removeItem(reelLineElements->at(i).at(j));
            reelLineElements->at(i).at(j)->~QGraphicsLineItem();
        }
        reelLineElements->at(i).clear();
    }
}

// false jak nie udalo sie otworzyc pliku, true w przeciwnym wypadku
// uwaga format pliku musi miec scisle okreslona strukture
bool CasinoGameWidget::readDataFromFile(string fileName)
{
    ifstream fileStream;
    string inputLine;
    int gapPosition = 0;

    fileStream.open(fileName, ios_base::in);
    if (fileStream.fail()){
        cout << "nie udalo sie otworzyc pliku" << endl;
        return false;
    }
    getline(fileStream, inputLine);

    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    reelQuantity = stoi(inputLine); //inputLine.substr(0, inputLine.size())
    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    symbolsDisplayedVerticallyOnScreenQuantity = stoi(inputLine);
    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    symbolQuantity = stoi(inputLine);
    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    linesQuantity = stoi(inputLine);
    inputLine.clear();

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < symbolQuantity; i++) // tyle co prizes->size()
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        prizes->push_back(*(new vector<int>()));
        for(unsigned int j = 0; j < reelQuantity; j++) // tyle co prizes->at(i).size()
        {
            gapPosition = inputLine.find(" ");
            inputLine.erase(0, gapPosition + 1);
            gapPosition = inputLine.find(" ");
            prizes->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < reelQuantity; i++) // tyle co reels->size()
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        reelIndexes->push_back(*(new vector<int>()));
        while(true) // liczba elementow na bebnie dowolna
        {
            gapPosition = inputLine.find(" ");
            if(gapPosition == string::npos)
                break;
            reelIndexes->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < linesQuantity; i++) // liczba linii dowolna
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        lines->push_back(*(new vector<int>()));
        for(unsigned int j = 0; j < reelQuantity; j++) // tyle co lines->at(i).size()
        {
            gapPosition = inputLine.find(" ");
            lines->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    fileStream.close();
    return true;
}
