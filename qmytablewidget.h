#pragma once

#include <QTableWidget>

#include "item.h"
#include "inventory.h"

class QMyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit QMyTableWidget(QWidget *parent = 0);

    void modelSync(Inventory &inv);

private:
    void updateCellView(QTableWidgetItem *item, const ItemDescription *type, int count);

private slots:
    void on_inventory_clicked(QTableWidgetItem *item);

protected:
    virtual void dropEvent(QDropEvent *event) override;
};
