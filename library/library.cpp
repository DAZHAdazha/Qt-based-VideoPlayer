#include <qboxlayout.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include "library.h"
#include "library/taglistmodel.h"
#include "videogriddelegate.h"

const QString kTagListQuery = "SELECT id, name FROM tags";

Library::Library(QWidget *parent) : QWidget(parent), db(Database("app.db")) {
    setWindowTitle("Library - Tomeo");
    setMinimumSize(1300, 720);
    setMaximumWidth(1280);
    setGeometry(50, 50, 1300, 720);

    addVideoForm = new Addvideo();
    connect(addVideoForm, SIGNAL(videoAdded(int)), this, SLOT(videoAdded(int)));
    connect(addVideoForm, SIGNAL(videoAddDone()), this, SLOT(videoAddDone()));

    addTagButton = new QPushButton("Add Tag");
    connect(addTagButton, SIGNAL(clicked()), this, SLOT(showAddTag()));

    tagCountText = new QLabel(this);

    tagListView = new QListView(this);
    tagListModel = new TagListModel;
    refreshTagCount();
    tagListView->setModel(tagListModel);
    tagListView->setModelColumn(1);
    connect(tagListView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectTag(QModelIndex)));

    searchText = new QLineEdit(this);

    searchButton = new QPushButton("Search");

    addVideoButton = new QPushButton("+");
    connect(addVideoButton, SIGNAL(clicked()), this, SLOT(showAddVideo()));

    videoGridView = new QListView(this);
    videoGridModel = new VideoGridModel(this);
    videoGridView->setModel(videoGridModel);
    videoGridView->setItemDelegate(new VideoGridDelegate);
    videoGridView->setViewMode(QListView::IconMode);
    videoGridView->setGridSize(QSize(250, 200));

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

void Library::showAddVideo() {
    addVideoForm->show();
}

void Library::showAddTag() {
    bool ok;
    QString text =
        QInputDialog::getText(this, tr("Add Tag"), tr("Name:"), QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty()) {
        auto record = tagListModel->record();
        record.remove(record.indexOf("id"));
        record.setValue("name", text);
        tagListModel->insertRecord(-1, record);
        refreshTagCount();
    }
}

void Library::refreshTagCount() {
    QString text;
    QTextStream(&text) << "Total Tags: " << tagListModel->rowCount();
    tagCountText->setText(text);
}

void Library::selectTag(const QModelIndex &index) {
    auto idIndex = tagListModel->index(index.row(), 0);
    auto id = idIndex.data().toInt();
    qDebug() << id;
}

void Library::videoAdded(int id) {
    qDebug() << "Video ID " << id;
}

void Library::videoAddDone() {
    videoGridModel->refresh();
}
