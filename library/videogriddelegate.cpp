#include "videogriddelegate.h"

#include <QtWidgets>

#include "videogridmodel.h"

void VideoGridDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const {
    auto data = index.data();
    if (!data.canConvert<VideoItem>()) {
        // Not our business
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    auto item = qvariant_cast<VideoItem>(data);
    auto rect = option.rect;

    if (item.widget->geometry() != rect) {
        item.widget->setGeometry(rect);
    }

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    auto originalPdev = painter->device();
    auto offset = painter->deviceTransform().map(QPoint(option.rect.x(), option.rect.y()));
    auto region = QRegion(0, 0, rect.width(), rect.height());

    painter->end();
    item.widget->render(painter->device(), offset, region, QWidget::RenderFlag::DrawChildren);
    painter->begin(originalPdev);
}

QSize VideoGridDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {
    auto data = index.data();
    if (data.canConvert<VideoItem>()) {
        auto item = qvariant_cast<VideoItem>(data);
        return item.widget->sizeHint();
    }
    return QStyledItemDelegate::sizeHint(option, index);
}
