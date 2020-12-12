#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QLabel>
#include <QString>

class PlaylistItem {
   public:
    explicit PlaylistItem(QString _title = QString(), QPixmap _pixmap = QPixmap())
        : pixmap(_pixmap), title(_title) {}
    QPixmap pixmap;
    QString title;
};

Q_DECLARE_METATYPE(PlaylistItem)

#endif  // PLAYLISTITEM_H