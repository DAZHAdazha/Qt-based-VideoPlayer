#include "videoitem.h"

#include <qboxlayout.h>

VideoItem::VideoItem(QPixmap _thumb, QString _title, QString _date, QString _location,
                     QString _memo)
    : thumb(_thumb), title(_title), date(_date), location(_location), memo(_memo) {
    widget = new QWidget;
    auto layout = new QHBoxLayout;
    auto innerLayout = new QVBoxLayout;

    QLabel *imgLabel = new QLabel();
    imgLabel->setStyleSheet("border:1px solid black;");
    QSize picSize(100,50);
    imgLabel->setPixmap(thumb.scaled(picSize, Qt::KeepAspectRatio));

    widget->setLayout(layout);

    QWidget *outerWindow = new QWidget();

    innerLayout->addWidget(imgLabel);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("border:1px solid black;");
    QLabel *dateLabel = new QLabel(date);
    dateLabel->setStyleSheet("border:1px solid black;");
    QLabel *locationLabel = new QLabel(location);
    locationLabel->setStyleSheet("border:1px solid black;");
    innerLayout->addWidget(titleLabel);
    innerLayout->addWidget(dateLabel);
    innerLayout->addWidget(locationLabel);

    outerWindow->setLayout(innerLayout);
    layout->addWidget(outerWindow);

    QLabel *memoLabel = new QLabel(memo);
    memoLabel->setStyleSheet("border:1px solid black;");
    layout->addWidget(memoLabel);


}
