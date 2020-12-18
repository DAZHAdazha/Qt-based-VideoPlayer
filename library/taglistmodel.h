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
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
};

#endif