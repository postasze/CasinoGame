#include <QMdiSubWindow>
#include "mainwindow.h"
#include "savingtofileform.h"
#include "generalsettingsform.h"
#include "linesettingform.h"
#include "prizesettingform.h"
#include "reelsettingform.h"
#include "resultdisplayform.h"
#include "readingfromfileform.h"
#include "computationform.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);

    connect(ui->actionZapisz, &QAction::triggered, this, &MainWindow::savingToFileFormOpened);
    connect(ui->actionUstawianie_og_lnych_parametr_w, &QAction::triggered, this, &MainWindow::generalSettingsFormOpened);
    connect(ui->actionUstawianie_linii, &QAction::triggered, this, &MainWindow::lineSettingFormOpened);
    connect(ui->actionUstawianie_nagr_d, &QAction::triggered, this, &MainWindow::prizeSettingFormOpened);
    connect(ui->actionustawianie_b_bn_w, &QAction::triggered, this, &MainWindow::reelSettingFormOpened);
    connect(ui->actionWy_wietlanie, &QAction::triggered, this, &MainWindow::resultDisplayFormOpened);
    connect(ui->actionWczytywanie_ustawie, &QAction::triggered, this, &MainWindow::readingFromFileFormOpened);
    connect(ui->actionWykonaj_obliczenia, &QAction::triggered, this, &MainWindow::computationFormOpened);

    this->reels = nullptr;
    this->lines = nullptr;
    this->prizes = nullptr;
    linesQuantity = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->resize(widget->width(), widget->height());
    //window->setWindowModality(Qt::WindowModal);
    window->show();
}

void MainWindow::removeSubWindow()
{
    this->ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::generalSettingsFormOpened()
{
    loadSubWindow(new GeneralSettingsForm(this));
}

void MainWindow::savingToFileFormOpened()
{
    loadSubWindow(new SavingToFileForm(this));
}

void MainWindow::lineSettingFormOpened()
{
    loadSubWindow(new LineSettingForm(this));
}

void MainWindow::prizeSettingFormOpened()
{
    loadSubWindow(new PrizeSettingForm(this));
}

void MainWindow::resultDisplayFormOpened()
{
    loadSubWindow(new ResultDisplayForm(this));
}

void MainWindow::reelSettingFormOpened()
{
    loadSubWindow(new ReelSettingForm(this));
}

void MainWindow::readingFromFileFormOpened()
{
    loadSubWindow(new ReadingFromFileForm(this));
}

void MainWindow::computationFormOpened()
{
    loadSubWindow(new ComputationForm(this));
}
