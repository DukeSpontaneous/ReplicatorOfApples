#include "qmytablewidget.h"

#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>
#include <QSound>

#include "database.h"

QMyTableWidget::QMyTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setDefaultDropAction(Qt::MoveAction);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragDrop);

    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setEnabled(false);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto &inv = Inventory::instance();
    this->setRowCount(inv.rows);
    this->setColumnCount(inv.cols);

    for (int row = 0; row < this->rowCount(); ++row)
    {
        for(int col = 0; col < this->columnCount(); ++col)
        {
            QTableWidgetItem *preItem = new QTableWidgetItem(QString(""));
            preItem->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            this->setItem(row, col, preItem);

            auto cell = inv.getCell(row, col);
            updateCellView(preItem, cell.first, cell.second);            
        }
    }

    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setDefaultSectionSize(100);
    this->verticalHeader()->setDefaultSectionSize(100);
    this->setIconSize(QSize(75, 75));
    this->setMaximumSize(302, 302);    

    connect(this, &QMyTableWidget::itemClicked,
            this, &QMyTableWidget::on_inventory_clicked);
}

QMyTableWidget::~QMyTableWidget()
{
}

void QMyTableWidget::modelSync(Inventory &inv)
{
    this->setRowCount(inv.rows);
    this->setColumnCount(inv.cols);

    for (int row = 0; row < this->rowCount(); ++row)
    {
        for(int col = 0; col < this->columnCount(); ++col)
        {
            auto cell = inv.getCell(row, col);
            updateCellView(this->item(row, col), cell.first, cell.second);
        }
    }
}

void QMyTableWidget::updateCellView(QTableWidgetItem *item, const ItemDescription *type, int count)
{
    QString iconPath = type == nullptr ? "" : type->imagePath;

    item->setText(count == 0 ? "" : QString::number(count));
    item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
    item->setIcon(QPixmap(iconPath));
}

// dropEvent(): Drop-event handler
void QMyTableWidget::dropEvent(QDropEvent *event)
{
    auto &inv = Inventory::instance();

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

        if (count > 0)
        {            
            QPair<const ItemDescription *, int> iDragCell, iDropCell;
            iDropCell = inv.getCell(item->row(), item->column());

            if (event->source() == this)
            {
                // if it is moving inside one table

                iDragCell = inv.getCell(row, col);

                if(iDropCell.first != nullptr)
                {
                    if(iDragCell.first != iDropCell.first)
                    {
                        event->ignore();
                        return;
                    }
                }

                inv.setCell(row, col, nullptr, 0);
            }
            else
            {
                iDragCell = inv.stubInexhaustibleApple();
            }

            count += item->text().toInt();
            inv.setCell(item->row(), item->column(), iDragCell.first, count);

            updateCellView(item, iDragCell.first, count);
        }
    }

    event->acceptProposedAction();
}

void QMyTableWidget::on_inventory_clicked(QTableWidgetItem *item)
{
    auto &inv = Inventory::instance();

    int row = item->row();
    int col = item->column();

    int count = item->text().toInt();

    if(count > 0)
    {
        auto cell = inv.getCell(row, col);

        QSound::play(cell.first->soundPath);

        --count;
        auto type = count == 0 ? nullptr : cell.first;
        inv.setCell(row, col, type, count);

        updateCellView(item, type, count);
    }
}
