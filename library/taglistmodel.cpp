#include "taglistmodel.h"
#include <qnamespace.h>

#include <QtCore>

bool TagListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole && index.column() == 1) {
        // Prevent overwriting existing tags
        auto newStrValue = value.toString();
        auto rows = rowCount();
        for (int i = 0; i < rows; i++) {
            auto curIndex = this->index(i, 1);
            if (curIndex.isValid() && curIndex.data(role).toString() == newStrValue) {
                return false;
            }
        }
    }
    return QSqlTableModel::setData(index, value, role);
}

Qt::ItemFlags TagListModel::flags(const QModelIndex &index) const {
    auto newFlags = QSqlTableModel::flags(index);
    if (index.isValid() && index.column() == 1) {
        auto tagName = index.data().toString();
        if (tagName == kTagAll || tagName == kTagUntagged) {
            newFlags &= ~Qt::ItemIsEditable;
        }
    }
    return newFlags;
}