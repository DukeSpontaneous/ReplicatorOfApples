#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmytablewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inventory->hide();
    ui->horizontalLayout_3->insertWidget(0, new QMyTableWidget(ui->inventory) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inventory_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
}
