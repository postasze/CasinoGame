#include "resultdisplayform.h"
#include "ui_resultdisplayform.h"

ResultDisplayForm::ResultDisplayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultDisplayForm)
{
    ui->setupUi(this);
    parentMdi = (MainWindow*) this->parentWidget();

    ui->plainTextEdit->setReadOnly(true);

    if(!parentMdi->computationResultString.isEmpty())
    {
        ui->plainTextEdit->setPlainText(parentMdi->computationResultString);
    }
}

ResultDisplayForm::~ResultDisplayForm()
{
    delete ui;
}
