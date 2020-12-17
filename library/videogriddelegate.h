#ifndef VIDEOGRIDDELEGATE_H
#define VIDEOGRIDDELEGATE_H

#include <QStyledItemDelegate>

class VideoGridDelegate : public QStyledItemDelegate {
    Q_OBJECT

   public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif