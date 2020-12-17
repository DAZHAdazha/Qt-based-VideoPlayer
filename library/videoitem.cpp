#include "videoitem.h"

#include <qboxlayout.h>
#include <qnamespace.h>

#include "utils.h"

const QString kCssNoBorder = "border: 0";

VideoItem::VideoItem(int _id, QString _path, QString _title, QString _date, QString _location,
                     QString _memo)
    : id(_id), path(_path), title(_title), date(_date), location(_location), memo(_memo) {
    widget = new QWidget;
    if (path.isEmpty()) {
        return;
    }
    widget->setAttribute(Qt::WA_DeleteOnClose);

    thumb = loadThumbnail(path);
    imgLabel = new QLabel();
    imgLabel->setStyleSheet("border:1px solid black;");
    QSize picSize(150, 75);
    imgLabel->setPixmap(thumb.scaled(picSize));
    imgLabel->setScaledContents(true);

    titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(kCssNoBorder);
    titleLabel->setFixedWidth(150);
    dateLabel = new QLabel(date);
    dateLabel->setStyleSheet(kCssNoBorder);
    dateLabel->setFixedWidth(150);
    locationLabel = new QLabel(location);
    locationLabel->setStyleSheet(kCssNoBorder);
    locationLabel->setFixedWidth(150);

    memoLabel = new QLabel(memo);
    memoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    memoLabel->setWordWrap(true);
    memoLabel->setStyleSheet("border:1px solid #BBBBBB;");
    memoLabel->setFixedWidth(70);

    initLayout();
}

void VideoItem::initLayout() {
    auto layout = new QHBoxLayout;
    auto innerLayout = new QVBoxLayout;
    auto infoLayout = new QVBoxLayout;

    QWidget *bottomWidget = new QWidget();

    bottomWidget->setStyleSheet("border:1px solid #BBBBBB;");

    innerLayout->addWidget(imgLabel, 1);
    innerLayout->setMargin(0);
    innerLayout->setAlignment(Qt::AlignBottom);
    innerLayout->addWidget(bottomWidget);

    infoLayout->setMargin(5);
    infoLayout->addWidget(titleLabel);
    infoLayout->addWidget(dateLabel);
    infoLayout->addWidget(locationLabel);

    auto outerWindow = new QWidget();
    outerWindow->setLayout(innerLayout);

    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(outerWindow, 3);
    layout->addWidget(memoLabel, 2);

    bottomWidget->setLayout(infoLayout);
    widget->setLayout(layout);
}