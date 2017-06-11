#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include "inventory.h"

// collapseButton(): animation collapsing button
void MainWindow::collapseButton(QPushButton *pButton)
{
    auto gExpand = pButton->geometry();
    auto gCollapsed = pButton->geometry();
    gCollapsed.setHeight(0);

    QPropertyAnimation *animation = new QPropertyAnimation(pButton, "geometry");
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(1000);
    animation->setStartValue(gExpand);
    animation->setEndValue(gCollapsed);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

// expandButton(): animation expanding button
void MainWindow::expandButton(QPushButton *pButton)
{
    auto gCollapsed = pButton->geometry();
    auto gExpand = pButton->geometry();
    gExpand.setHeight(23);

    QPropertyAnimation *animation = new QPropertyAnimation(pButton, "geometry");
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(1000);
    animation->setStartValue(gCollapsed);
    animation->setEndValue(gExpand);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inventory->hide();

    myInventory = new QMyTableWidget(this);
    ui->horizontalLayout_3->insertWidget(0, myInventory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// on_buttonStart_clicked(): slot for buttonStart->clicked()
void MainWindow::on_buttonStart_clicked()
{
    if(ui->buttonStart->isEnabled() == false)
        return;

    ui->buttonStart->setEnabled(false);
    ui->buttonExit->setEnabled(false);

    ui->buttonMainMenu->setEnabled(true);
    ui->applesSource->setEnabled(true);
    myInventory->setEnabled(true);

    collapseButton(ui->buttonStart);
    collapseButton(ui->buttonExit);

    auto &inv = Inventory::instance();
    inv.clean();
    myInventory->modelSync(inv);
}

// on_buttonMainMenu_clicked(): slot for buttonMainMenu->clicked()
void MainWindow::on_buttonMainMenu_clicked()
{
    if(ui->buttonMainMenu->isEnabled() == false)
        return;

    ui->buttonStart->setEnabled(true);
    ui->buttonExit->setEnabled(true);

    ui->buttonMainMenu->setEnabled(false);
    ui->applesSource->setEnabled(false);
    myInventory->setEnabled(false);

    expandButton(ui->buttonStart);
    expandButton(ui->buttonExit);
}

// on_buttonMainMenu_clicked(): slot for buttonExit->clicked()
void MainWindow::on_buttonExit_clicked()
{
    this->close();
}


