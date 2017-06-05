#pragma once

#include "item.h"

#include <QString>
#include <QtSql>
#include <QVector>

#include <tuple>

class Database
{
    QSqlDatabase db;

public:
    Database(QString path);

    static QSqlDatabase &instance();
};

namespace DB
{
    namespace Inventory
    {
        QVector<std::tuple<int, int, int, int> > getCells();
        bool updateCell(int row, int col, ItemType type, int count);
    }
}
