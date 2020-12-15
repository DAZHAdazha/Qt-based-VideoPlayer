#include "library.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include "videogriddelegate.h"

Library::Library(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Library - Tomeo");
    setMinimumSize(1280, 720);
    setGeometry(0, 0, 1280, 720);

    addTagButton = new QPushButton("Add Tag");

    tagListView = new QListView(this);
    tagCountText = new QLabel(this);
    tagCountText->setText("Total Tags: 0");

    searchText = new QLineEdit(this);

    searchButton = new QPushButton("Search");

    addVideoButton = new QPushButton("+");

    videoGridView = new QListView(this);
    videoGridModel = new VideoGridModel(4, this);
    videoGridView->setModel(videoGridModel);
    videoGridView->setItemDelegate(new VideoGridDelegate);
    videoGridView->setViewMode(QListView::IconMode);
    videoGridView->setGridSize(QSize(100, 100));

    initLayout();
}

Library::~Library() {}

void Library::initLayout() {
    auto leftPanel = new QWidget(this);
    auto leftLayout = new QVBoxLayout;
    leftPanel->setLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignTop);

    leftLayout->addWidget(addTagButton);
    leftLayout->addWidget(tagListView, 1);
    leftLayout->addWidget(tagCountText);

    auto rightPanel = new QWidget(this);
    auto rightLayout = new QVBoxLayout;
    rightPanel->setLayout(rightLayout);
    rightLayout->setAlignment(Qt::AlignTop);

    auto topBar = new QWidget(this);
    auto topBarLayout = new QHBoxLayout;
    topBar->setLayout(topBarLayout);
    topBarLayout->setMargin(0);
    topBarLayout->setAlignment(Qt::AlignCenter);

    topBarLayout->addStretch(1);
    topBarLayout->addWidget(searchText, 3);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch(1);
    topBarLayout->addWidget(addVideoButton);

    rightLayout->addWidget(topBar);
    rightLayout->addWidget(videoGridView, 1);

    auto layout = new QHBoxLayout;
    layout->addWidget(leftPanel, 2);
    layout->addWidget(rightPanel, 10);

    setLayout(layout);
}
