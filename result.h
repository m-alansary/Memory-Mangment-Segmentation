#ifndef RESULT_H
#define RESULT_H
#include <QDialog>
#include<QtCore>
#include<QtGui>
#include <QGraphicsScene>
#include<QGraphicsItem>
#include <QDialog>
#include <QDialog>
#include"addprocess.h"

namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = nullptr);
    ~result();

private slots:
    void on_push_clicked();

    void on_deallocate_clicked();

    void on_pushButton_clicked();

private:
    Ui::result *ui;
    QGraphicsScene * scene ;
    QGraphicsRectItem *rect;
    QStandardItemModel *model;
    QStandardItemModel *model1;

};

#endif // RESULT_H
