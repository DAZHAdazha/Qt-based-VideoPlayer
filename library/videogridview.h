#ifndef VIDEOGRIDVIEW_H
#define VIDEOGRIDVIEW_H

#include <qnamespace.h>

#include <QtWidgets>

#include "videogridmodel.h"

class VideoGridView : public QListView {
   public:
    explicit VideoGridView(QWidget *parent = 0, VideoGridModel *model = 0);

   protected:
    void keyPressEvent(QKeyEvent *event) override;

   private:
    VideoGridModel *model;
};

#endif