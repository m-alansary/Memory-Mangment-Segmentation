#ifndef FILLHOLES_H
#define FILLHOLES_H
#include<QtCore>
#include<QDialog>
#include<QtGui>
#include <QDialog>
#include<delegate.h>
#include <QKeyEvent>
#include <QDialog>
#include<hole.h>
namespace Ui {
class FillHoles;
}

class FillHoles : public QDialog
{
    Q_OBJECT

public:
    explicit FillHoles(QWidget *parent = nullptr);
    ~FillHoles();
    friend bool sort_holes( const std::vector<int>& v1,
                            const std::vector<int>& v2 );

private slots:
    void on_submit_clicked();

private:
    Ui::FillHoles *ui;
    QStandardItemModel *model;
    Delegate * mydatalate;
};

#endif // FILLHOLES_H
