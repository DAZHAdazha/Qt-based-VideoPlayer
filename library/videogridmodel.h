#ifndef VIDEOGRIDMODEL_H
#define VIDEOGRIDMODEL_H

#include <QAbstractListModel>
#include <QSqlQueryModel>

#include "videoitem.h"

class VideoGridModel : public QSqlQueryModel {
    Q_OBJECT
   public:
    explicit VideoGridModel(QWidget *parent) : QSqlQueryModel(parent) {
        refresh();
    }
    void refresh();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setTagId(int id);
    int tagId() const;

   private:
    VideoItem createItemFrom(int id, int row) const;
    int m_tagId = 0;
    QMap<int, VideoItem> m_data;
};

#endif
