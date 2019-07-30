#include "reelsettingform.h"
#include "ui_reelsettingform.h"
#include "reelelement.h"

ReelSettingForm::ReelSettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReelSettingForm)
{
    //vector<int> *newReelPointer;
    QString comboBoxItem;
    ReelElement *reelElementPointer, *previousReelElementPointer;
    //QWidget *widgetPointer;
    QScrollArea *scrollAreaPointer;

    reels = new vector<vector<int>>();

    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();
    //ui->scrollArea->setVisible(false);

    for(unsigned int i = 0; i < parentMdi->symbolQuantity; i++)
    {
        comboBoxItem += "Symbol " + QString::number(i+1);
        ui->symbolComboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
    ui->symbolComboBox->setCurrentIndex(0);
    currentSymbol = 1;

    connect(ui->symbolComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &ReelSettingForm::symbolComboBoxCurrentIndexChanged);

    if(parentMdi->reels != nullptr)
        *this->reels = *parentMdi->reels; // kopia

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
    {
        if(parentMdi->reels == nullptr)
            reels->push_back(*(new vector<int>()));

        scrollAreaPointer = new QScrollArea(this);
        scrollAreaPointer->move(50+70*i, 200);
        scrollAreaPointer->resize(68, 50 * parentMdi->symbolsDisplayedVerticallyOnScreenQuantity);
        scrollAreaPointer->show();
        reelScenePointer = new QGraphicsScene(scrollAreaPointer);
        //reelScenePointer->setItemIndexMethod(QGraphicsScene::NoIndex);
        reelViewPointer = new QGraphicsView(reelScenePointer, scrollAreaPointer);
        reelScenePointer->setSceneRect(0, 0, 50, 50*parentMdi->symbolsDisplayedVerticallyOnScreenQuantity);
        reelViewPointer->setSceneRect(0, 0, 50, 50*parentMdi->symbolsDisplayedVerticallyOnScreenQuantity);
        reelViewPointer->setBackgroundBrush(Qt::white);
        //reelViewPointer->move(50+70*i, 150);
        reelViewPointer->show();
        //reelViewPointers[i] = reelViewPointer;
        scrollAreaPointer->setWidget(reelViewPointer);
        reelViewPointer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        reelViewPointer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        if(parentMdi->reels == nullptr)
        {
            reelElementPointer = new ReelElement(nullptr, reelViewPointer, this, QPointF(50+70*i, 150), true, i, -1, nullptr);
            reelViewPointer->scene()->addItem(reelElementPointer);
            //newReelPointer = new vector<int>();
            //reels.push_back(*newReelPointer);
        }
        else
        {
            previousReelElementPointer = nullptr;
            for(unsigned int j = 0; j < parentMdi->reels->at(i).size(); j++)
            {
                reelViewPointer->resize(50, reelViewPointer->height() + 50);
                reelViewPointer->setSceneRect(0, 0, 50, reelViewPointer->height());
                reelElementPointer = new ReelElement(nullptr, reelViewPointer, this, QPointF(50+70*i, 150), false, i, this->reels->at(i).at(j), previousReelElementPointer);
                previousReelElementPointer = reelElementPointer;
                reelElementPointer->setY(50 * j);
                //this->coordinates.setY(this->coordinates.y() + 50);
                reelViewPointer->scene()->addItem(reelElementPointer);
            }
            reelElementPointer = new ReelElement(nullptr, reelViewPointer, this, QPointF(50+70*i, 150), true, i, -1, previousReelElementPointer);
            reelElementPointer->setY(previousReelElementPointer->y() + 50);
            reelViewPointer->scene()->addItem(reelElementPointer);
        }
    }
}

ReelSettingForm::~ReelSettingForm()
{
    delete ui;
}

void ReelSettingForm::symbolComboBoxCurrentIndexChanged(int index)
{
    currentSymbol = index + 1;
}

void ReelSettingForm::on_buttonBox_accepted()
{
    if(parentMdi->reels != nullptr)
        free(parentMdi->reels);
    parentMdi->reels = this->reels;
    this->~ReelSettingForm();
    this->parentMdi->removeSubWindow();
}

void ReelSettingForm::on_buttonBox_rejected()
{
    this->~ReelSettingForm();
    this->parentMdi->removeSubWindow();
}
