#include "library.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qpalette.h>
#include "library/taglistmodel.h"
#include "player.h"
#include "videogriddelegate.h"

const QString kTagListQuery = "SELECT id, name FROM tags";
const QFont kFontRoboto("RobotoCondensed-Regular", 12, QFont::Normal);
const QFont kFontEczer("Eczar-Regular", 12, QFont::Normal);

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
    addTagButton->setFont(kFontRoboto);
    addTagButton->setIcon(QIcon(":/tag.png"));
    addTagButton->setIconSize(QSize(25, 25));
    removeTagButton = new QPushButton("Delete");
    removeTagButton->setFont(kFontRoboto);
    removeTagButton->setIcon(QIcon(":/delete.png"));
    removeTagButton->setIconSize(QSize(25, 25));
    connect(addTagButton, SIGNAL(clicked()), this, SLOT(showAddTag()));
    tagCountText = new QLabel(this);
    tagCountText->setFont(kFontEczer);
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
    removeVideoButton = new QPushButton();
    removeVideoButton->setIcon(QIcon(":/delete.png"));
    removeVideoButton->setIconSize(QSize(25, 25));
    videoGridModel = new VideoGridModel(this);
    videoGridView = new VideoGridView(this, videoGridModel);
    connect(videoGridView, SIGNAL(activated(QModelIndex)), this, SLOT(selectVideo(QModelIndex)));
    connect(videoGridView, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(videoGridCtxMenu(QPoint)));
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
    defaultSortButton->setFont(kFontRoboto);
    defaultSortButton->setChecked(true);
    connect(defaultSortButton, SIGNAL(clicked()), this, SLOT(defaultSort()));
    nameSortButton = new QRadioButton(this);
    nameSortButton->setText("Name");
    nameSortButton->setFont(kFontRoboto);
    connect(nameSortButton, SIGNAL(clicked()), this, SLOT(nameSort()));
    dateSortButton = new QRadioButton(this);
    dateSortButton->setText("Date");
    dateSortButton->setFont(kFontRoboto);
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
    auto rightPanel = new QWidget(this);
    auto rightLayout = new QVBoxLayout;
    auto topBar = new QWidget(this);
    auto topBarLayout = new QHBoxLayout;
    auto colorbar = new QWidget();
    auto buttonbar = new QWidget();
    auto buttonLayout = new QHBoxLayout();
    auto topWidget = new QWidget();
    auto topWidgetLayout = new QHBoxLayout;
    auto layout = new QHBoxLayout;
    leftPanel->setLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignTop);
    topWidget->setLayout(topWidgetLayout);
    topWidgetLayout->addWidget(addTagButton);
    topWidgetLayout->addWidget(removeTagButton);
    topWidgetLayout->setMargin(5);
    topWidgetLayout->setSpacing(10);
    topWidget->setStyleSheet("background-color: #4A6572");
    leftLayout->addWidget(topWidget,1);
    leftLayout->addWidget(tagListView, 8);
    leftLayout->addWidget(tagCountText,1);
    leftLayout->setMargin(0);
    leftLayout->setSpacing(1);
    rightPanel->setLayout(rightLayout);
    rightLayout->setAlignment(Qt::AlignTop);
    buttonbar->setLayout(buttonLayout);
    buttonLayout->addWidget(addVideoButton);
    buttonLayout->addWidget(removeVideoButton);
    colorbar->setStyleSheet("background-color:#B0BEC5");
    buttonbar->setStyleSheet("background-color:#B0BEC5");
    setStyle(*topBarLayout);
    topBar->setLayout(topBarLayout);
    topBarLayout->addWidget(colorbar,6);
    topBarLayout->addWidget(buttonbar,1);
    videoGridView->setStyleSheet("background-color: #ECEFF1");
    rightLayout->addWidget(topBar);
    rightLayout->addWidget(videoGridView, 1);
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);
    layout->addWidget(leftPanel, 2);
    layout->addWidget(rightPanel, 10);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
}

void Library::setStyle(QHBoxLayout& topBarLayout){
    topBarLayout.setMargin(0);
    topBarLayout.setAlignment(Qt::AlignCenter);
    topBarLayout.addWidget(sortWidget,3);
    topBarLayout.setMargin(0);
    topBarLayout.setSpacing(0);

    addTagButton->setStyleSheet("background-color: #F9AA33");
    removeTagButton->setStyleSheet("background-color: #F9AA33");
    tagCountText->setStyleSheet("background-color:#232F34");
    tagCountText->setContentsMargins(10,10,10,10);
    tagListView->setStyleSheet("background-color:#344955;color:white;");
    tagListView->setFont(kFontRoboto);
    tagListView->setSpacing(5);
    sortWidget->setStyleSheet("background-color:#B0BEC5");
    addVideoButton->setStyleSheet("background-color:#F9AA33");
    removeVideoButton->setStyleSheet("background-color:#F9AA33");
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
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    tagCountText->setPalette(pe);
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

void Library::videoGridCtxMenu(const QPoint &pos) {
    auto index = videoGridView->indexAt(pos);
    if (!index.isValid()) return;

    if (videoGridMenu == nullptr) {
        videoGridMenu = new QMenu(this);
        auto deleteAction = new QAction("Delete", this);
        connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteCurrentVideo()));
        videoGridMenu->addAction(deleteAction);
    }

    videoGridMenu->popup(videoGridView->viewport()->mapToGlobal(pos));
}

void Library::deleteCurrentVideo() {
    videoGridView->deleteCurrentVideo();
}
