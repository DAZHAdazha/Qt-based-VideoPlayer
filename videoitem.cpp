#include "videoitem.h"

#include <qboxlayout.h>

VideoItem::VideoItem(QPixmap _thumb, QString _title, QString _date, QString _location,
                     QString _memo)
    : thumb(_thumb), title(_title), date(_date), location(_location), memo(_memo) {
    widget = new QWidget;
    auto layout = new QVBoxLayout;
    widget->setLayout(layout);
    layout->addWidget(new QLabel(title));
    layout->addWidget(new QLabel(date));
}