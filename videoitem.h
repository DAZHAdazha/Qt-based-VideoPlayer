#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QLabel>
#include <QString>

class VideoItem {
   public:
    VideoItem(QPixmap _thumb = QPixmap(), QString _title = QString(), QString _date = QString(),
              QString _location = QString(), QString _memo = QString());
    QPixmap thumb;
    QString title;
    QString date;
    QString location;
    QString memo;
    QWidget* widget;
};

Q_DECLARE_METATYPE(VideoItem)
#endif