#ifndef DIALOGXX_H
#define DIALOGXX_H

#include <QDialog>

namespace Ui {
class Dialogxx;
}

class Dialogxx : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogxx(QWidget *parent = nullptr);
    ~Dialogxx();

private:
    Ui::Dialogxx *ui;
};

#endif // DIALOGXX_H
