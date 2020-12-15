#ifndef VIDEOGRIDMODEL_H
#define VIDEOGRIDMODEL_H

#include <QAbstractListModel>

#include "videoitem.h"

class VideoGridModel : public QAbstractListModel {
    Q_OBJECT
   public:
    explicit VideoGridModel(int _gridSize, QWidget *parent)
        : gridSize(_gridSize), QAbstractListModel(parent) {
        for(int i=0;i<20;i++){
            m_data.push_back(VideoItem(QPixmap("D:\\IDMdownload\\videos\\a.png"), "Title", "_DATE_", "Location", "Memo"));
        }

    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;

   private:
    int gridSize;
    QVector<VideoItem> m_data;
};

#endif
