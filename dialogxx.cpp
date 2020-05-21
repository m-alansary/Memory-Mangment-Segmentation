#include "dialogxx.h"
#include "ui_dialogxx.h"

Dialogxx::Dialogxx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogxx)
{
    ui->setupUi(this);
}

Dialogxx::~Dialogxx()
{
    delete ui;
}
