#include "database.h"

#include<QtGlobal>
#include<QHash>

Database::Database(QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (db.open() == false)
    {
        qDebug() << db.lastError().text();
        db.close();
    }
}

Database::~Database()
{
    db.close();
}

QSqlDatabase &Database::instance()
{
    if ( ! QFile::exists("./db.sqlite"))
    {
        QFile sourceFile( ":/database/db.sqlite" );
        QFile destFile( "./db.sqlite" );
        bool success = true;
        success &= sourceFile.open( QFile::ReadOnly );
        success &= destFile.open( QFile::WriteOnly | QFile::Truncate );
        success &= destFile.write( sourceFile.readAll() ) >= 0;
        sourceFile.close();
        destFile.close();
    }

    static Database database("./db.sqlite");
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
        bool updateCell(int row, int col, int type, int count)
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

    namespace ItemTypes
    {
        void dbSync(QHash<int, const ItemDescription *> *items)
        {
            auto &db = Database::instance();

            QSqlQuery query("SELECT * FROM item_types");

            while (query.next() )
            {
                ItemDescription *item = new ItemDescription(
                            query.value("id").toInt(),
                            query.value("image").toString(),
                            query.value("sound").toString());
                items->insert(item->type, item);
            }
        }
    }
}
