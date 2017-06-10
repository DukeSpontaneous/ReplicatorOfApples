#pragma once

#include "item.h"

#include <QString>
#include <QtSql>
#include <QVector>

#include <tuple>

/*
II.3. Класс "База данных". Необходим для управления базой данных.
Подключается к базе данных и выполняет запросы. Использовать QSqlDatabase.
*/
class Database
{
    QSqlDatabase db;

public:
    Database(QString path);
    ~Database();

    static QSqlDatabase &instance();
};

/*
II.4. База данных SQLite. Содержит в себе таблицы "Инвентарь" и "Предмет", которые хранят данные указанных выше классов.
Здесь должны отражаться названия предметов, нажождение их в каких либо ячейках инвентаря. Конкретная организация таблиц на ваше усмотрение.
*/
namespace DB
{    
    namespace Inventory
    {
        QVector<std::tuple<int, int, int, int> > getCells();
        bool updateCell(int row, int col, int type, int count);
    }

    namespace ItemTypes
    {
        void dbSync(QHash<int, const ItemDescription *> *items);
    }
}
