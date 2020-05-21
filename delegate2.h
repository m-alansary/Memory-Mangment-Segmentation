#ifndef DELEGATE2_H
#define DELEGATE2_H
#include<QStyledItemDelegate>

class delegate2 : public QStyledItemDelegate
{
     Q_OBJECT
public:
    explicit delegate2(QWidget*parent= nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const;
};

#endif // DELEGATE2_H
