#include "videogridview.h"

#include <qkeysequence.h>
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qsqlerror.h>

#include "videogriddelegate.h"

VideoGridView::VideoGridView(QWidget *parent, VideoGridModel *model)
    : QListView(parent), model(model) {
    setFocusPolicy(Qt::StrongFocus);
    setModel(model);
    setItemDelegate(new VideoGridDelegate);
    setViewMode(QListView::IconMode);
    setGridSize(QSize(250, 200));
}

void VideoGridView::keyPressEvent(QKeyEvent *event) {
    auto index = currentIndex();
    if (event->matches(QKeySequence::Delete) && index.isValid()) {
        if (QMessageBox::question(
                this, "Delete", "Delete the video from this tag? The file will not be affected.") ==
            QMessageBox::Yes) {
            QSqlQuery query;
            query.prepare("DELETE FROM videos WHERE tag_id = ? AND id = ?");
            auto item = qvariant_cast<VideoItem>(index.data());

            query.addBindValue(model->tagId());
            query.addBindValue(item.id);
            query.exec();

            model->refresh();
        }
    }
    QListView::keyPressEvent(event);
}