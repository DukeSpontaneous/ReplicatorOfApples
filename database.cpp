#include "database.h"

#include<QtGlobal>

Database::Database(QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (false == db.open() )
    {
        qDebug() << db.lastError().text();
        db.close();
    }
}

QSqlDatabase &Database::instance()
{
    static Database database("./database/db.sqlite");
    return database.db;
}

namespace DB
{
    namespace Inventory
    {
        // getCells(): get a list of inventory cells from the database
        QVector<std::tuple<int, int, int, int> > getCells()
        {
            auto &db = Database::instance();

            QSqlQuery query("SELECT * FROM inventory");

            QVector<std::tuple<int, int, int, int> > cells;

            while (query.next() )
            {
                cells.push_back(
                    std::tuple<int, int, int, int> {
                        query.value("row").toInt(),
                        query.value("column").toInt(),
                        query.value("item_type").toInt(),
                        query.value("count").toInt()
                    }
                );
            }

            return cells;
        }

        // updateCell(): update the inventory cell in the database
        bool updateCell(int row, int col, ItemType type, int count)
        {
            auto &db = Database::instance();

            QString str("UPDATE inventory SET item_type = %1, count = %2 WHERE row = %3 AND column = %4");

            str = str
                .arg(QString::number(type) )
                .arg(QString::number(count) )
                .arg(QString::number(row + 1) )
                .arg(QString::number(col + 1) );

            QSqlQuery query;

            bool res = query.exec(str);

            if (false == res)
            {
                qDebug() << query.lastError().text();
            }

            return res;
        }
    }
}
