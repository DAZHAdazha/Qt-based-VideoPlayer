#ifndef VIDEOGRIDMODEL_H
#define VIDEOGRIDMODEL_H

#include <QAbstractListModel>

#include "videoitem.h"

class VideoGridModel : public QAbstractListModel {
    Q_OBJECT
   public:
    explicit VideoGridModel(int _gridSize, QWidget *parent)
        : gridSize(_gridSize), QAbstractListModel(parent) {
        m_data.push_back(VideoItem(QPixmap(), "Title", "_DATE_", "", ""));
        m_data.push_back(VideoItem(QPixmap(), "Title2", "_DATE_2", "", ""));
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;

   private:
    int gridSize;
    QVector<VideoItem> m_data;
};

#endif