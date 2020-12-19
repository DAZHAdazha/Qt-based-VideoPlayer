#include "library.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include "library/taglistmodel.h"
#include "player.h"
#include "videogriddelegate.h"

const QString kTagListQuery = "SELECT id, name FROM tags";

Library::Library(QWidget *parent) : QWidget(parent), db(Database("app.db")) {
    setWindowTitle("Library - Tomeo");
    setMinimumSize(1300, 720);
    setMaximumWidth(1280);
    setGeometry(50, 50, 1300, 720);

    player = new Player(nullptr, this);

    addVideoForm = new AddVideoForm();
    connect(addVideoForm, SIGNAL(videoAdded(int)), this, SLOT(videoAdded(int)));
    connect(addVideoForm, SIGNAL(videoAddDone()), this, SLOT(videoAddDone()));

    addTagButton = new QPushButton("Add Tag");
    addTagButton->setIcon(QIcon(":/tag.png"));
    addTagButton->setIconSize(QSize(25, 25));
    connect(addTagButton, SIGNAL(clicked()), this, SLOT(showAddTag()));

    tagCountText = new QLabel(this);

    tagListView = new QListView(this);
    tagListModel = new TagListModel;
    refreshTagCount();
    tagListView->setModel(tagListModel);
    tagListView->setModelColumn(1);
    connect(tagListView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectTag(QModelIndex)));

    initSort();

    addVideoButton = new QPushButton();
    addVideoButton->setIcon(QIcon(":/add.png"));
    addVideoButton->setIconSize(QSize(25, 25));
    connect(addVideoButton, SIGNAL(clicked()), this, SLOT(showAddVideo()));

    videoGridView = new QListView(this);
    videoGridModel = new VideoGridModel(this);
    videoGridView->setModel(videoGridModel);
    videoGridView->setItemDelegate(new VideoGridDelegate);
    videoGridView->setViewMode(QListView::IconMode);
    videoGridView->setGridSize(QSize(250, 200));
    connect(videoGridView, SIGNAL(activated(QModelIndex)), this, SLOT(selectVideo(QModelIndex)));

    // Select the first tag
    auto firstTagIndex = tagListModel->index(0, 1);
    tagListView->setCurrentIndex(firstTagIndex);
    selectTag(firstTagIndex);

    initLayout();
}

Library::~Library() {}

void Library::initSort() {
    auto sortLayout = new QHBoxLayout();
    sortWidget = new QWidget(this);

    sortButtonGroup = new QButtonGroup(this);
    defaultSortButton = new QRadioButton(this);
    defaultSortButton->setText("Default");
    defaultSortButton->setChecked(true);
    connect(defaultSortButton, SIGNAL(clicked()), this, SLOT(defaultSort()));
    nameSortButton = new QRadioButton(this);
    nameSortButton->setText("Name");
    connect(nameSortButton, SIGNAL(clicked()), this, SLOT(nameSort()));
    dateSortButton = new QRadioButton(this);
    dateSortButton->setText("Date");
    connect(dateSortButton, SIGNAL(clicked()), this, SLOT(dateSort()));
    sortButtonGroup->addButton(nameSortButton);
    sortButtonGroup->addButton(dateSortButton);
    sortButtonGroup->addButton(defaultSortButton);
    sortLayout->addWidget(defaultSortButton, 1);
    sortLayout->addWidget(nameSortButton, 1);
    sortLayout->addWidget(dateSortButton, 1);
    sortLayout->setAlignment(Qt::AlignLeft);
    sortWidget->setLayout(sortLayout);
}

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

    topBarLayout->addWidget(sortWidget);
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
    addVideoForm->setTagId(videoGridModel->tagId());
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
    videoGridModel->setTagId(id);
}

void Library::videoAdded(int id) {
    qDebug() << "Added video ID" << id;
}

void Library::videoAddDone() {
    videoGridModel->refresh();
}

void Library::defaultSort() {
    videoGridModel->setSortType(kSortDefault);
}

void Library::nameSort() {
    videoGridModel->setSortType(kSortName);
}

void Library::dateSort() {
    videoGridModel->setSortType(kSortDate);
}

void Library::selectVideo(const QModelIndex &index) {
    QList<QUrl> urls;
    // Index of path is 4
    for (int i = 0; i < videoGridModel->rowCount(); i++) {
        auto pathIndex = videoGridModel->index(i, 4);
        auto pathStr = pathIndex.data().toString();
        urls << QUrl::fromLocalFile(pathStr);
    }
    player->clearPlaylist();
    player->addToPlaylist(urls);
    player->setTagName(tagListView->currentIndex().data().toString());
    player->show();
    player->activateWindow();
    player->jumpToRow(index.row());
}
