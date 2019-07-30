#include "savingtofileform.h"
#include "ui_savingtofileform.h"

SavingToFileForm::SavingToFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SavingToFileForm)
{
    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();
}

SavingToFileForm::~SavingToFileForm()
{
    delete ui;
}

// false jak nie udalo sie utworzyc pliku, true w przeciwnym wypadku
// uwaga program powinien miec juz wszystkie ustawienia i wykonane obliczenia przed zapisem do pliku
bool SavingToFileForm::saveDataToFile(string fileName)
{
  ofstream fileStream;
  fileStream.open(fileName, ios_base::out);

  if (fileStream.fail()){
      return false;
  }
  else
  {
    fileStream << parentMdi->computationResultString.toStdString();

    fileStream.close();
  }
  return true;
}

void SavingToFileForm::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() == "")
        return;

    saveDataToFile(ui->lineEdit->text().toStdString());
    this->~SavingToFileForm();
    this->parentMdi->removeSubWindow();
}

void SavingToFileForm::on_buttonBox_rejected()
{
    this->~SavingToFileForm();
    this->parentMdi->removeSubWindow();
}
