#ifndef ADDPROCESS_H
#define ADDPROCESS_H
#include<QtCore>
#include<QDialog>
#include<QtGui>
#include <QDialog>
#include<delegate.h>
#include<delegate2.h>
#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class addprocess;
}

class addprocess : public QDialog
{
    Q_OBJECT

public:
    explicit addprocess(QWidget *parent = nullptr);
    QString * temp1;
    QString * temp3;
    int * temp2;
    ~addprocess();

private slots:
    void on_push_clicked();

private:
    Ui::addprocess *ui;
    QStandardItemModel *model;
    QStandardItemModel *model2;
    Delegate * mydatalate;
    delegate2 * mydelegate;

};

#endif // ADDPROCESS_H
