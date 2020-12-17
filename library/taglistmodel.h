#ifndef TAGLISTMODEL_H
#define TAGLISTMODEL_H

#include <QSqlTableModel>

const QString kTagAll = "All";
const QString kTagUntagged = "Untagged";

class TagListModel : public QSqlTableModel {
    Q_OBJECT

   public:
    explicit TagListModel() : QSqlTableModel() {
        setTable("tags");
        select();
    }
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
};

#endif