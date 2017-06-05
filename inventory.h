#pragma once

#include "item.h"

#include <QPair>
#include <QVector>

class Inventory
{
    int rows;
    int cols;

    QVector<QPair<ItemType, int> > cells;

private:
    QPair<ItemType, int> &getCell(int row, int col);

public:
    Inventory();
    ~Inventory() = default;

    static Inventory &instance();

    // Only for init
    void setItem(int row, int col, ItemType item, int count);

    void addItem(int row, int col, ItemType item, int count);
    void removeItem(int row, int col);

};
