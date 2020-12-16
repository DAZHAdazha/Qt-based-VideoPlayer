#include "videoitem.h"

#include <qboxlayout.h>

VideoItem::VideoItem(QPixmap _thumb, QString _title, QString _date, QString _location,
                     QString _memo)
    : thumb(_thumb), title(_title), date(_date), location(_location), memo(_memo) {
    widget = new QWidget;
    auto layout = new QHBoxLayout;
    auto innerLayout = new QVBoxLayout;
    auto infoLayout = new QVBoxLayout;

    layout->setAlignment(Qt::AlignTop);

    QLabel *imgLabel = new QLabel();
    imgLabel->setStyleSheet("border:1px solid black;");
    QSize picSize(150, 75);
    imgLabel->setPixmap(thumb.scaled(picSize));
    imgLabel->setScaledContents(true);

    widget->setLayout(layout);

    QWidget *outerWindow = new QWidget();
    QWidget *bottomWidget = new QWidget();

    bottomWidget->setStyleSheet("border:1px solid #BBBBBB;");

    innerLayout->addWidget(imgLabel, 1);
    innerLayout->setMargin(0);
    innerLayout->setAlignment(Qt::AlignBottom);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("border:0px solid #BBBBBB;");
    titleLabel->setFixedWidth(150);
    QLabel *dateLabel = new QLabel(date);
    dateLabel->setStyleSheet("border:0px solid #BBBBBB;");
    dateLabel->setFixedWidth(150);
    QLabel *locationLabel = new QLabel(location);
    locationLabel->setStyleSheet("border:0px solid #BBBBBB;");
    locationLabel->setFixedWidth(150);
    innerLayout->addWidget(bottomWidget);

    infoLayout->setMargin(5);
    infoLayout->addWidget(titleLabel);
    infoLayout->addWidget(dateLabel);
    infoLayout->addWidget(locationLabel);
    bottomWidget->setLayout(infoLayout);

    outerWindow->setLayout(innerLayout);
    layout->addWidget(outerWindow, 3);

    QLabel *memoLabel = new QLabel(memo);
    memoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    memoLabel->setWordWrap(true);
    memoLabel->setStyleSheet("border:1px solid #BBBBBB;");
    memoLabel->setFixedWidth(70);
    layout->addWidget(memoLabel, 2);
}
