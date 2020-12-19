#include "videogridmodel.h"

#include <QtCore>

QVariant VideoGridModel::data(const QModelIndex &cIndex, int role) const {
    if (cIndex.isValid() && role == Qt::DisplayRole && cIndex.column() == 0) {
        auto ret = QVariant();
        int row = cIndex.row();
        if (m_data.contains(row)) {
            auto value = m_data[row];
            ret.setValue(value);
        } else {
            auto id = QSqlQueryModel::data(cIndex, role).toInt();
            auto item = createItemFrom(id, row);
            const_cast<VideoGridModel *>(this)->m_data[row] = item;
            ret.setValue(item);
        }
        return ret;
    }
    return QSqlQueryModel::data(cIndex, role);
}

VideoItem VideoGridModel::createItemFrom(int id, int row) const {
    auto path = index(row, 4).data().toString();
    auto title = index(row, 1).data().toString();
    auto dateStr = index(row, 2).data().toString();
    auto item = VideoItem(id, path, title, dateStr, index(row, 3).data().toString(),
                          index(row, 5).data().toString());
    return item;
}

void VideoGridModel::setTagId(int id) {
    m_tagId = id;
    qDebug() << "Setting tag id to " << id;
    refresh();
}

int VideoGridModel::tagId() const {
    return m_tagId;
}

void VideoGridModel::setSortType(int t) {
    sortType = t;
    refresh();
}

void VideoGridModel::refresh() {
    QString query;
    QTextStream queryStream(&query);
    queryStream << "SELECT * FROM `videos` WHERE tag_id = " << m_tagId;
    if (sortType == kSortDate) {
        queryStream << " ORDER BY date DESC";
    } else if (sortType == kSortName) {
        queryStream << " ORDER BY title ASC";
    }
    m_data.clear();
    setQuery(query);
}
