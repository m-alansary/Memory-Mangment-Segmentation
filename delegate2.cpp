#include "delegate2.h"
#include<QLineEdit>
delegate2::delegate2(QWidget*parent):QStyledItemDelegate(parent)
{

}
QWidget *delegate2 ::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const{
    QLineEdit* lineEdit = new QLineEdit(parent);
      lineEdit->setMaxLength(10); // or whatever...
      return lineEdit;
}
