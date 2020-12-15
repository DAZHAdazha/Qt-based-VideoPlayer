#include "videogridmodel.h"

QVariant VideoGridModel::data(const QModelIndex &index, int role) const {
    auto ret = QVariant();
    if (index.isValid() && role == Qt::DisplayRole && index.row() < m_data.size()) {
        auto value = m_data[index.row()];
        ret.setValue(value);
    }
    return ret;
}

int VideoGridModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_data.size();
}