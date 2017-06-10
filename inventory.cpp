#include "inventory.h"
#include "database.h"

Inventory::Inventory()
{
    this->rows = 3;
    this->cols = 3;

    this->cells.resize(this->rows * this->cols);

    dbSync();
}

Inventory &Inventory::instance()
{
    static Inventory inv;
    return inv;
}

// getCell(): get the contents of the inventory cell by row and column
QPair<const ItemDescription *, int> &Inventory::getCell(int row, int col)
{
    return this->cells[row * this->cols + col];
}

// setCell(): set the contents of the inventory cell by row and column
void Inventory::setCell(int row, int col, const ItemDescription *item, int count)
{
    QPair<const ItemDescription *, int> &pair = this->getCell(row, col);

    pair.first = item;
    pair.second = count;

    DB::Inventory::updateCell(row,
                              col,
                              pair.first == nullptr ? 0 : pair.first->type,
                              pair.second);
}

void Inventory::clean()
{
    for (int row = 0; row < this->rows; ++row)
    {
        for(int col = 0; col < this->cols; ++col)
        {
            this->setCell(row, col, nullptr, 0);
        }
    }
}

// dbSyncInventory(): set the contents of the inventory cell by row and column
void Inventory::dbSync()
{
    DB::ItemTypes::dbSync(&descriptions);

    inexhaustibleApple.first = descriptions[1];
    inexhaustibleApple.second = 1;

    QVector<std::tuple<int, int, int, int> > list = DB::Inventory::getCells();

    for (auto &item : list)
    {
        const int row = std::get<0>(item) - 1;
        const int col = std::get<1>(item) - 1;
        const int type = std::get<2>(item);
        const int count = std::get<3>(item);

        auto &pair = this->getCell(row, col);

        pair.first = descriptions[type];
        pair.second = count;
    }
}

QPair<const ItemDescription *, int> &Inventory::stubInexhaustibleApple()
{
    return inexhaustibleApple;
}
