#include "qmytablewidget.h"

#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>

#include "inventory.h"
#include "item.h"
#include "database.h"

QMyTableWidget::QMyTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setDefaultDropAction(Qt::MoveAction);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragDrop);

    this->setDragEnabled(true);
    this->setAcceptDrops(true);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setMaximumSize(302, 302);

    this->setRowCount(3);
    this->setColumnCount(3);

    for (int i = 0; i < this->rowCount(); ++i)
    {
        for(int j = 0; j < this->columnCount(); ++j)
        {
            QTableWidgetItem *protoitem = new QTableWidgetItem(QString(""));
            protoitem->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            this->setItem(i, j, protoitem);
        }
    }

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setDefaultSectionSize(100);
    this->verticalHeader()->setDefaultSectionSize(100);

    auto &inv = Inventory::instance();

    QVector<std::tuple<int, int, int, int> > list = DB::Inventory::getCells();

    for (auto &item : list)
    {
        const int row = std::get<0>(item) - 1;
        const int col = std::get<1>(item) - 1;
        const int type = std::get<2>(item);
        const int count = std::get<3>(item);

        this->item(row, col)->setText(QString::number(count) );

        inv.setItem(row, col, static_cast<ItemType>(type), count);
    }
}

QMyTableWidget::~QMyTableWidget()
{
}

// dropEvent(): Drop-event handler
void QMyTableWidget::dropEvent(QDropEvent *event)
{
    const int x = event->pos().x();
    const int y = event->pos().y();

    QTableWidgetItem *item = itemAt(x, y);

    if (item == nullptr)
    {
        event->ignore();
        return;
    }

    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        int count = roleDataMap[0].toInt();

        auto &inv = Inventory::instance();

        if (count > 0)
        {
            inv.addItem(item->row(), item->column(), ItemType::Apple, count);

            if (event->source() == this)
            {
                inv.removeItem(row, col);
            }

            QString sum = QString::number(item->text().toInt() + count);
            item->setText(sum);
        }
    }

    event->acceptProposedAction();
}
