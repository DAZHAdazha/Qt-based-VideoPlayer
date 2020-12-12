#include "playlistdelegate.h"

#include <QtWidgets>

#include "playlistitem.h"

const int kRowHeight = 70;
const int kThumbWidth = kRowHeight * (16.0 / 9.0);

void PlaylistDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
    auto data = index.data();
    if (data.canConvert<PlaylistItem>()) {
        auto item = qvariant_cast<PlaylistItem>(data);
        auto rect = option.rect;

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
        else if (option.state & QStyle::State_MouseOver)
            painter->fillRect(option.rect, option.palette.midlight());

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        auto thumbRect = QRect(rect);
        thumbRect.setHeight(kRowHeight);
        thumbRect.setWidth(kThumbWidth);
        thumbRect = thumbRect.marginsRemoved(QMargins(4, 4, 4, 4));
        painter->drawPixmap(thumbRect, item.pixmap);

        if (rect.width() > kThumbWidth) {
            auto textRect = QRect(rect);
            textRect.setLeft(rect.left() + kThumbWidth);
            painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeading, item.title);
        }

        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize PlaylistDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    auto data = index.data();
    if (data.canConvert<PlaylistItem>()) {
        auto width = option.rect.width();
        return QSize(width, kRowHeight);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}