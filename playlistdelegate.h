#ifndef PLAYLISTDELEGATE_H
#define PLAYLISTDELEGATE_H

#include <QStyledItemDelegate>

class PlaylistDelegate : public QStyledItemDelegate {
    Q_OBJECT

   public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif  // PLAYLISTDELEGATE_H