#ifndef VIDEOGRIDMODEL_H
#define VIDEOGRIDMODEL_H

#include <QAbstractListModel>
#include <QSqlQueryModel>

#include "videoitem.h"

const int kSortDefault = 0;
const int kSortName = 1;
const int kSortDate = 2;

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
    void setSortType(int t);

   private:
    VideoItem createItemFrom(int id, int row) const;
    int m_tagId = 0;
    int sortType = kSortDefault;
    QMap<int, VideoItem> m_data;
};

#endif
