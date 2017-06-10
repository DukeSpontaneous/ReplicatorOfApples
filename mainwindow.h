#pragma once

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPushButton>

#include "qmytablewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMyTableWidget *myInventory;

    void collapseButton(QPushButton *pButton);
    void expandButton(QPushButton *pButton);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonStart_clicked();

    void on_buttonMainMenu_clicked();

    void on_buttonExit_clicked();

private:
    Ui::MainWindow *ui;
};
