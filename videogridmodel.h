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
            m_data.push_back(VideoItem(QPixmap("D:\\IDMdownload\\videos\\a.png"), "Title", "jkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjk", "asdfghjklasdfg", "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."));
        }

    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;

   private:
    int gridSize;
    QVector<VideoItem> m_data;
};

#endif
