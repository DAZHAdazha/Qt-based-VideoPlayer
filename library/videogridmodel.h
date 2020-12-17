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
   private slots:
    void beginInsertItems(int start, int end);
    void endInsertItems();
    void beginRemoveItems(int start, int end);
    void endRemoveItems();
    void changeItems(int start, int end);

   private:
    VideoItem createItemFrom(int id, int row) const;
    int gridSize;
    QMap<int, VideoItem> m_data;
};

#endif
