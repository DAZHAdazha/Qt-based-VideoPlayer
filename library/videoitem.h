#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QLabel>
#include <QString>

class VideoItem {
   public:
    VideoItem(int _id = -1, QString _path = QString(), QString _title = QString(),
              QString _date = QString(), QString _location = QString(), QString _memo = QString());
    int id;
    QPixmap thumb;
    QString path;
    QString title;
    QString date;
    QString location;
    QString memo;

    QWidget* widget;
    QLabel* imgLabel;
    QLabel* titleLabel;
    QLabel* dateLabel;
    QLabel* locationLabel;
    QLabel* memoLabel;

   private:
    void initLayout();
};

Q_DECLARE_METATYPE(VideoItem)
#endif