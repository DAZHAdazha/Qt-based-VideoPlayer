#ifndef LIBRARY_H
#define LIBRARY_H

#include <qlineedit.h>

#include <QWidget>

#include "addvideo.h"
#include "database.h"
#include "videogridview.h"
#include "taglistmodel.h"
#include "videogridmodel.h"

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QAbstractButton;
class QLabel;
class QLineEdit;
class QListView;
QT_END_NAMESPACE

class Player;

class Library : public QWidget {
    Q_OBJECT

   public:
    Library(QWidget* parent = 0);
    ~Library();

   private slots:
    void showAddVideo();
    void showAddTag();
    void selectTag(const QModelIndex& index);
    void videoAdded(int id);
    void videoAddDone();
    void defaultSort();
    void nameSort();
    void dateSort();
    void selectVideo(const QModelIndex& index);
    void videoGridCtxMenu(const QPoint& pos);
    void deleteCurrentVideo();

   private:
    void initLayout();
    void initSort();
    void refreshTagCount();

    QAbstractButton* addTagButton;
    QAbstractButton* removeTagButton;
    QListView* tagListView;
    TagListModel* tagListModel;
    QLabel* tagCountText;

    QWidget* sortWidget;
    QButtonGroup* sortButtonGroup;
    QRadioButton* defaultSortButton;
    QRadioButton* nameSortButton;
    QRadioButton* dateSortButton;
    QAbstractButton* addVideoButton;
    QAbstractButton* removeVideoButton;

    VideoGridView* videoGridView;
    VideoGridModel* videoGridModel;

    Database db;
    AddVideoForm* addVideoForm;
    Player* player;

    QMenu* videoGridMenu = nullptr;
};

#endif
