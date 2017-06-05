#include "inventory.h"
#include "database.h"

Inventory::Inventory()
{
    this->rows = 3;
    this->cols = 3;

    this->cells.resize(this->rows * this->cols);
}

Inventory &Inventory::instance()
{
    static Inventory inv;
    return inv;
}

// getCell(): get the contents of the inventory cell by row and column
QPair<ItemType, int> &Inventory::getCell(int row, int col)
{
    return this->cells[row * this->cols + col];
}

// setItem(): set the contents of the inventory cell by row and column
void Inventory::setItem(int row, int col, ItemType item, int count)
{
    auto &pair = this->getCell(row, col);

    pair.first = item;
    pair.second = count;
}

// addItem(): increase the number of items in the inventory cell
void Inventory::addItem(int row, int col, ItemType item, int count)
{
    auto &pair = this->getCell(row, col);

    pair.first = item;
    pair.second += count;

    DB::Inventory::updateCell(row, col, pair.first, pair.second);
}

// removeItem(): remove items from inventory cell
void Inventory::removeItem(int row, int col)
{
    auto &pair = this->getCell(row, col);

    pair.first = ItemType::None;
    pair.second = 0;

    DB::Inventory::updateCell(row, col, pair.first, pair.second);
}
