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
        // for (int i = 0; i < 20; i++) {
        //     m_data.push_back(VideoItem(
        //         "/home/harryc/hdd/workspace/leeds/ui-cw3/videos/a.mp4", "Title",
        //         "jkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjkjk", "asdfghjklasdfg",
        //         "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem
        //         " "Ipsum has been the industry's standard dummy text ever since the 1500s, when
        //         an " "unknown printer took a galley of type and scrambled it to make a type
        //         specimen " "book. It has survived not only five centuries, but also the leap into
        //         electronic " "typesetting, remaining essentially unchanged. It was popularised in
        //         the 1960s " "with the release of Letraset sheets containing Lorem Ipsum passages,
        //         and more " "recently with desktop publishing software like Aldus PageMaker
        //         including versions " "of Lorem Ipsum."));
        // }
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
