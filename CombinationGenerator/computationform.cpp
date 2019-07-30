#include "computationform.h"
#include "ui_computationform.h"
#include <iostream>

using namespace std;

ComputationForm::ComputationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComputationForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->acceptButton->setDisabled(true);
    currentSymbol = 0;
    prizeSum = 0;
    combinationsQuantity = 1;
    combinationsComputed = 0;
    noPrizeCombinationsQuantity = 0;

    connect(ui->acceptButton, &QPushButton::clicked, this, &ComputationForm::acceptButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ComputationForm::cancelButtonClicked);
    connect(ui->computationButton, &QPushButton::clicked, this, &ComputationForm::computationButtonClicked);

    symbolCountsOnLine = new vector<int>();
    reelIndexes = new vector<int>();

    for(unsigned int i = 0; i < parentMdi->symbolQuantity; i++)
        symbolCountsOnLine->push_back(0);

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++)
        reelIndexes->push_back(0);
}

ComputationForm::~ComputationForm()
{
    delete ui;
}

void ComputationForm::computationButtonClicked()
{
    bool noPrizeCombination;

    for(unsigned int i = 0; i < parentMdi->reels->size(); i++) // tyle co parentMdi->reelQuantity
        combinationsQuantity *= parentMdi->reels->at(i).size(); // liczba elementow na bebnie dowolna

    computationResultString += "Ogolne informacje\n";
    computationResultString += "Liczba bebnow: " + QString::number(parentMdi->reelQuantity) + "\n";
    computationResultString += "Liczba elementow widzianych w pionie na ekranie: "
            + QString::number(parentMdi->symbolsDisplayedVerticallyOnScreenQuantity) + "\n";
    computationResultString += "Liczba symboli: " + QString::number(parentMdi->symbolQuantity) + "\n";
    computationResultString += "Liczba linii: " + QString::number(parentMdi->linesQuantity) + "\n\n";

    computationResultString += "Nagrody\n";
    for(unsigned int i = 0; i < parentMdi->prizes->size(); i++) // tyle co parentMdi->symbolQuantity
    {
        computationResultString += "nagrody za wielokrotnosci symbolu nr " + QString::number(i+1) + "\n";
        for(unsigned int j = 0; j < parentMdi->prizes->at(i).size(); j++) // tyle co parentMdi->reelQuantity
            computationResultString += QString::number(j+1) +": " + QString::number(parentMdi->prizes->at(i).at(j)) + " "; // wielkosc nagordy dowolna
        computationResultString += "\n";
    }
    computationResultString += "\n";

    computationResultString += "Bebny\n";
    for(unsigned int i = 0; i < parentMdi->reels->size(); i++) // tyle co parentMdi->reelQuantity
    {
        computationResultString += "symbole wystepujace na bebnie nr " + QString::number(i) + "\n";
        for(unsigned int j = 0; j < parentMdi->reels->at(i).size(); j++) // liczba elementow na bebnie dowolna
            computationResultString += QString::number(parentMdi->reels->at(i).at(j)) + " "; // nr symbolu <= max symbolQuantity
        computationResultString += "\n";
    }
    computationResultString += "\n";

    computationResultString += "Linie\n";
    for(unsigned int i = 0; i < parentMdi->lines->size(); i++) // liczba linii dowolna
    {
        computationResultString += "punkty przez ktore przechodzi linia o nr " + QString::number(i+1) + "\n";
        for(unsigned int j = 0; j < parentMdi->lines->at(i).size(); j++) // tyle co parentMdi->reelQuantity
            computationResultString += QString::number(parentMdi->lines->at(i).at(j)) + " "; // punkt na linii <= ilosc symboli w pionie
        computationResultString += "\n";
    }
    computationResultString += "\n";

    //cout << computationResultString.toStdString() << endl;

    computationResultString += "Kombinacje\n";
    allCombinationsComputed = false;
    while(true)
    {
        noPrizeCombination = true;
        /*computationResultString += "Kombinacja: ";
        for(unsigned int i = 0; i < reelIndexes->size(); i++) // tyle co parentMdi->reelQuantity
            computationResultString += QString::number(reelIndexes->at(i)) + " ";
        computationResultString += "\n";*/

        for(unsigned int i = 0; i < parentMdi->lines->size(); i++) // liczba linii dowolna
        {
            for(unsigned int j = 0; j < parentMdi->lines->at(i).size(); j++) // tyle co parentMdi->reelQuantity
            {
                currentSymbol = parentMdi->reels->at(j).at((reelIndexes->at(j) + parentMdi->lines->at(i).at(j)) % parentMdi->reels->at(j).size());
                currentSymbol--;
                symbolCountsOnLine->at(currentSymbol) += 1;
            }

            for(unsigned int j = 0; j < symbolCountsOnLine->size(); j++) // tyle co parentMdi->symbolQuantity
            {
                if(symbolCountsOnLine->at(j) > 0 && (parentMdi->prizes->at(j).at(symbolCountsOnLine->at(j)-1) > 0))
                {
                    /*computationResultString += "nagroda za ilosc symboli: " + QString::number(symbolCountsOnLine->at(j))
                        + " o numerze: " + QString::number(j+1) + " znajdujacych sie na linii o numerze " + QString::number(i+1)
                        + " wynosi: " + QString::number(parentMdi->prizes->at(j).at(symbolCountsOnLine->at(j)-1)) + "\n";
                    */prizeSum += parentMdi->prizes->at(j).at(symbolCountsOnLine->at(j)-1);
                    noPrizeCombination = false;
                }
            }
            for(unsigned int j = 0; j < symbolCountsOnLine->size(); j++) // tyle co parentMdi->symbolQuantity
                symbolCountsOnLine->at(j) = 0; // czyszczenie wystapien symboli
        }

        if(noPrizeCombination)
            noPrizeCombinationsQuantity++;

        reelIndexes->at(0)++;
        for(unsigned int i = 0; i < parentMdi->reelQuantity; i++) // tyle jest w sumie indeksow
        {
            if(reelIndexes->at(i) == parentMdi->reels->at(i).size())
            {
                if(i == parentMdi->reelQuantity - 1)
                {
                    allCombinationsComputed = true;
                    break;
                }
                reelIndexes->at(i) = 0;
                reelIndexes->at(i+1)++;
            }
        }
        if(allCombinationsComputed)
            break;

        combinationsComputed++;
        ui->progressBar->setValue(100.0f * (combinationsComputed / combinationsQuantity));
    }

    computationResultString += "\n";
    computationResultString += "suma nagrod wynosi: " + QString::number(prizeSum) + "\n";
    computationResultString += "liczba wszystkich kombinacji wynosi: " + QString::number(combinationsQuantity) + "\n";
    computationResultString += "liczba wszystkich kombinacji pomnozona przez liczbe linii wynosi: " +
        QString::number(combinationsQuantity*parentMdi->lines->size()) + "\n";
    computationResultString += "liczba kombinacji nie dajacych zadnej nagrody wynosi: " +
        QString::number(noPrizeCombinationsQuantity) + "\n";
    computationResultString += "% zysku gracza wynosi: " +
        QString::number(100.0f * (prizeSum / (combinationsQuantity*parentMdi->lines->size()))) + "\n";
    computationResultString += "% kombinacji nie dajacych zadnej nagrody wynosi: " +
        QString::number(100.0f * (noPrizeCombinationsQuantity / combinationsQuantity)) + "\n";

    ui->progressBar->setValue(100);
    ui->acceptButton->setEnabled(true);
}

void ComputationForm::acceptButtonClicked()
{
    parentMdi->computationResultString = this->computationResultString;
    this->~ComputationForm();
    this->parentMdi->removeSubWindow();
}

void ComputationForm::cancelButtonClicked()
{
    this->~ComputationForm();
    this->parentMdi->removeSubWindow();
}
