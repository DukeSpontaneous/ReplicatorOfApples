#pragma once

#include "item.h"

#include <QPair>
#include <QVector>
#include <QHash>



/*
II.2. Класс "Инвентарь". Должен описывать инвентарь и содержать поля размер (количество ячеек), а так же поля,
описывающие, в какой ячейке сколько находится предметов и каких предметов.
*/
class Inventory
{
private:
    QHash<int, const ItemDescription *> descriptions;
    QVector<QPair<const ItemDescription *, int> > cells;

    QPair<const ItemDescription *, int> inexhaustibleApple;

public:
    int rows;
    int cols;

private:
    void dbSync();

public:
    Inventory();
    ~Inventory() = default;

    static Inventory &instance();

    QPair<const ItemDescription *, int> &getCell(int row, int col);
    void setCell(int row, int col, const ItemDescription *item, int count);
    void clean();

    QPair<const ItemDescription *, int> &stubInexhaustibleApple();
};
