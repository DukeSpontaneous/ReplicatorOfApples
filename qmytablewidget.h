#ifndef QMYTABLEWIDGET_H
#define QMYTABLEWIDGET_H

#include <QTableWidget>

class QMyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit QMyTableWidget(QWidget *parent = 0);
    ~QMyTableWidget();

protected:
    virtual void dropEvent(QDropEvent *event) override;
};

#endif // QMYTABLEWIDGET_H
