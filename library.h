#ifndef LIBRARY_H
#define LIBRARY_H

#include <qlineedit.h>

#include <QWidget>

#include "videogridmodel.h"
#include "addvideo.h"

#include "database.h"

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QAbstractButton;
class QLabel;
class QLineEdit;
class QListView;
QT_END_NAMESPACE

class Library : public QWidget {
    Q_OBJECT

   public:
    Library(QWidget* parent = 0);
    ~Library();

   private slots:
    void showAddVideo();
    void showAddTag();
    void selectTag(const QModelIndex &index);
   private:
    void initLayout();
    void refreshTags();

    QAbstractButton* addTagButton;
    QListView* tagListView;
    QSqlQueryModel* tagListModel;
    QLabel* tagCountText;

    QLineEdit* searchText;
    QAbstractButton* searchButton;
    QAbstractButton* addVideoButton;

    QListView* videoGridView;
    VideoGridModel* videoGridModel;

    Database db;
    Addvideo *addvideo;

};

#endif
