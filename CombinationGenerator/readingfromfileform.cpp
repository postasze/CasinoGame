#include "readingfromfileform.h"
#include "ui_readingfromfileform.h"
#include <iostream>

using namespace std;

ReadingFromFileForm::ReadingFromFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadingFromFileForm)
{
    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();
}

ReadingFromFileForm::~ReadingFromFileForm()
{
    delete ui;
}

// false jak nie udalo sie otworzyc pliku, true w przeciwnym wypadku
// uwaga format pliku musi miec scisle okreslona strukture
bool ReadingFromFileForm::readDataFromFile(string fileName)
{
    ifstream fileStream;
    char character;
    string inputLine;
    int gapPosition = 0;

    fileStream.open(fileName, ios_base::in);
    if (fileStream.fail()){
        cout << "nie udalo sie otworzyc pliku" << endl;
        return false;
    }
    parentMdi->computationResultString.clear();
    while(fileStream.get(character))
        parentMdi->computationResultString += character;
    fileStream.close();

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
    parentMdi->reelQuantity = stoi(inputLine); //inputLine.substr(0, inputLine.size())
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
    parentMdi->symbolsDisplayedVerticallyOnScreenQuantity = stoi(inputLine);
    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    parentMdi->symbolQuantity = stoi(inputLine);
    inputLine.clear();

    getline(fileStream, inputLine);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    gapPosition = inputLine.find(" ");
    inputLine.erase(0, gapPosition + 1);
    parentMdi->linesQuantity = stoi(inputLine);
    inputLine.clear();

    if(parentMdi->reels != nullptr)
        free(parentMdi->reels);
    if(parentMdi->prizes != nullptr)
        free(parentMdi->prizes);
    if(parentMdi->lines != nullptr)
        free(parentMdi->lines);

    parentMdi->reels = new vector<vector<int>>();
    parentMdi->prizes = new vector<vector<int>>();
    parentMdi->lines = new vector<vector<int>>();

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < parentMdi->symbolQuantity; i++) // tyle co parentMdi->prizes->size()
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        parentMdi->prizes->push_back(*(new vector<int>()));
        for(unsigned int j = 0; j < parentMdi->reelQuantity; j++) // tyle co parentMdi->prizes->at(i).size()
        {
            gapPosition = inputLine.find(" ");
            inputLine.erase(0, gapPosition + 1);
            gapPosition = inputLine.find(" ");
            parentMdi->prizes->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < parentMdi->reelQuantity; i++) // tyle co parentMdi->reels->size()
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        parentMdi->reels->push_back(*(new vector<int>()));
        while(true) // liczba elementow na bebnie dowolna
        {
            gapPosition = inputLine.find(" ");
            if(gapPosition == string::npos)
                break;
            parentMdi->reels->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    getline(fileStream, inputLine);
    inputLine.clear();
    getline(fileStream, inputLine);
    inputLine.clear();

    for(unsigned int i = 0; i < parentMdi->linesQuantity; i++) // liczba linii dowolna
    {
        getline(fileStream, inputLine);
        inputLine.clear();
        getline(fileStream, inputLine);
        parentMdi->lines->push_back(*(new vector<int>()));
        for(unsigned int j = 0; j < parentMdi->reelQuantity; j++) // tyle co parentMdi->lines->at(i).size()
        {
            gapPosition = inputLine.find(" ");
            parentMdi->lines->at(i).push_back(stoi(inputLine.substr(0, gapPosition)));
            inputLine.erase(0, gapPosition + 1);
        }
    }

    fileStream.close();
    return true;
}

void ReadingFromFileForm::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() == "")
        return;

    readDataFromFile(ui->lineEdit->text().toStdString());
    this->~ReadingFromFileForm();
    this->parentMdi->removeSubWindow();
}

void ReadingFromFileForm::on_buttonBox_rejected()
{
    this->~ReadingFromFileForm();
    this->parentMdi->removeSubWindow();
}
