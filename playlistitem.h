#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QLabel>
#include <QString>

class PlaylistItem {
   public:
    explicit PlaylistItem(QString _title = QString(), QString _location = QString(), QPixmap _pixmap = QPixmap())
        : pixmap(_pixmap), title(_title), location(_location) {}
    QPixmap pixmap;
    QString title;
    QString location;
};

Q_DECLARE_METATYPE(PlaylistItem)

#endif  // PLAYLISTITEM_H
