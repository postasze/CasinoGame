#include "linesettingform.h"
#include "ui_linesettingform.h"
#include <iostream>

using namespace std;

LineSettingForm::LineSettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineSettingForm)
{
    QString comboBoxItem;
    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();

    scenePointer = new QGraphicsScene(this);
    viewPointer = new QGraphicsView(scenePointer, this);
    scenePointer->setSceneRect(0, 0, 50*parentMdi->reelQuantity, 50*parentMdi->symbolsDisplayedVerticallyOnScreenQuantity);
    viewPointer->setSceneRect(0, 0, 50*parentMdi->reelQuantity, 50*parentMdi->symbolsDisplayedVerticallyOnScreenQuantity);
    viewPointer->setBackgroundBrush(Qt::white);
    viewPointer->move(100, 150);
    viewPointer->show();

    lines = new vector<vector<int>>();
    squareElements = new vector<vector<SquareElement*>>();
    lineElements = new vector<QGraphicsLineItem*>();

    connect(ui->newLinePushButton, &QPushButton::clicked, this, &LineSettingForm::addNewLinePushButtonClicked);
    connect(ui->saveLinePushButton, &QPushButton::clicked, this, &LineSettingForm::saveLinePushButtonClicked);
    connect(ui->deleteLinePushButton, &QPushButton::clicked, this, &LineSettingForm::deleteLinePushButtonClicked);
    connect(ui->lineComboBox, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged), this, &LineSettingForm::lineComboBoxCurrentIndexChanged);

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
    {
        squareElements->push_back(*(new vector<SquareElement*>()));
        for(unsigned int j = 0; j < parentMdi->symbolsDisplayedVerticallyOnScreenQuantity; j++)
        {
            squareElementPointer = new SquareElement(nullptr, this, viewPointer, QPointF(100, 150), i);
            squareElementPointer->moveBy(50*i, 50*j);
            viewPointer->scene()->addItem(squareElementPointer);
            squareElements->at(i).push_back(squareElementPointer);
        }
    }
    //lineComboBoxCount = 0;
    isEditingEnabled = false;
    currentLineIndex = -1;

    if(parentMdi->lines != nullptr)
    {
        *this->lines = *parentMdi->lines; // kopia
        for(unsigned int i = 0; i < lines->size(); i++)
        {
            comboBoxItem += "Linia " + QString::number(i + 1);
            ui->lineComboBox->addItem(comboBoxItem);
            comboBoxItem.clear();
        }
    }
}

LineSettingForm::~LineSettingForm()
{
    delete ui;
}

void LineSettingForm::lineComboBoxCurrentIndexChanged(int index)
{
    currentLineIndex = index;
    vector<int> *points;

    //lineComboBoxCount++;
    //if(lineComboBoxCount == 1)
    //    return;

    points = &lines->at(index);

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
    {
        clearReel(i);
        squareElements->at(i).at(points->at(i))->selected = true;
    }
    updateLine();

    isEditingEnabled = true;
}

void LineSettingForm::addNewLinePushButtonClicked()
{
    if(isEditingEnabled)
        return;

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
        squareElements->at(i).at(0)->selected = true;
    updateLine();
    isEditingEnabled = true;
}

void LineSettingForm::saveLinePushButtonClicked()
{
    vector<int> *newPoints = new vector<int>(), *points;
    QString comboBoxItem;
    bool lineExists;

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++) // zapisywanie nowej linii
    {
        for(unsigned int j = 0; j < parentMdi->symbolsDisplayedVerticallyOnScreenQuantity; j++)
        {
            if(squareElements->at(i).at(j)->selected == true)
                newPoints->push_back(j);
        }
    }

    if(newPoints->empty())
        return;

    for(unsigned int i = 0; i < lines->size(); i++) // sprawdzenie czy dana linia juz istnieje
    {
        points = &lines->at(i);
        lineExists = true;
        for(unsigned int j = 0; j < parentMdi->reelQuantity; j++)
        {
            if(points->at(j) != newPoints->at(j))
            {
                lineExists = false;
                break;
            }
        }
        if(lineExists)
            break;
    }

    if(!lineExists)
    {
        lines->push_back(*newPoints);
        for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
            clearReel(i);
        updateLine();

        isEditingEnabled = false;
        comboBoxItem += "Linia " + QString::number(lines->size());
        ui->lineComboBox->addItem(comboBoxItem);
        comboBoxItem.clear();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Wiadomość");
        messageBox.setText("Dana linia została już wprowadzona wcześniej");
        messageBox.exec();
    }
}

void LineSettingForm::deleteLinePushButtonClicked()
{
    vector<vector<int>> *temporaryLines;
    vector<int> temporaryLine;
    int linesCount = 0, temporaryLinesCount = 0;

    if(lines->empty())
        return;

    if(currentLineIndex == -1)
        return;

    if(!isEditingEnabled)
        return;

    temporaryLines = new vector<vector<int>>();
    linesCount = lines->size();
    for(unsigned int i = currentLineIndex; i < linesCount; i++)
    {
        temporaryLine = lines->back();
        temporaryLines->push_back(temporaryLine);
        lines->pop_back();
    }
    temporaryLines->pop_back();
    temporaryLinesCount = temporaryLines->size();
    for(unsigned int i = 0; i < temporaryLinesCount; i++)
    {
        temporaryLine = temporaryLines->back();
        lines->push_back(temporaryLine);
        temporaryLines->pop_back();
    }

    ui->lineComboBox->removeItem(ui->lineComboBox->count() - 1);
    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
        clearReel(i);
    updateLine();
    isEditingEnabled = false;
}

void LineSettingForm::on_buttonBox_accepted()
{
    if(parentMdi->lines != nullptr)
        free(parentMdi->lines);
    parentMdi->lines = this->lines;
    parentMdi->linesQuantity = this->lines->size();
    this->~LineSettingForm();
    this->parentMdi->removeSubWindow();
}

void LineSettingForm::on_buttonBox_rejected()
{
    this->~LineSettingForm();
    this->parentMdi->removeSubWindow();
}

void LineSettingForm::clearReel(int reelIndex)
{
    for(unsigned int i = 0; i < parentMdi->symbolsDisplayedVerticallyOnScreenQuantity; i++)
        squareElements->at(reelIndex).at(i)->selected = false;
}

void LineSettingForm::updateLine()
{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    QGraphicsLineItem *lineElementPointer;

    vector<QGraphicsLineItem*>::iterator iter = lineElements->begin();
    while (iter != lineElements->end())
    {
        viewPointer->scene()->removeItem(*iter);
        (*iter)->~QGraphicsLineItem();
        iter++;
    }
    lineElements->clear();

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
    {
        for(unsigned int j = 0; j < parentMdi->symbolsDisplayedVerticallyOnScreenQuantity; j++)
        {
            squareElements->at(i).at(j)->update();
            if(squareElements->at(i).at(j)->selected)
            {
                if(i == 0)
                {
                    x1 = squareElements->at(i).at(j)->x() + 25;
                    y1 = squareElements->at(i).at(j)->y() + 25;
                    continue;
                }
                if(i == (parentMdi->reelQuantity - 1))
                {
                    x2 = squareElements->at(i).at(j)->x() + 25;
                    y2 = squareElements->at(i).at(j)->y() + 25;
                    lineElementPointer = new QGraphicsLineItem(x1, y1, x2, y2);
                    lineElementPointer->setPen(QPen(QBrush(Qt::red), 5));
                    lineElements->push_back(lineElementPointer);
                    viewPointer->scene()->addItem(lineElementPointer);
                    continue;
                }
                x2 = squareElements->at(i).at(j)->x() + 25;
                y2 = squareElements->at(i).at(j)->y() + 25;
                lineElementPointer = new QGraphicsLineItem(x1, y1, x2, y2);
                lineElementPointer->setPen(QPen(QBrush(Qt::red), 5));
                lineElements->push_back(lineElementPointer);
                viewPointer->scene()->addItem(lineElementPointer);
                x1 = squareElements->at(i).at(j)->x() + 25;
                y1 = squareElements->at(i).at(j)->y() + 25;
            }
        }
    }
}
