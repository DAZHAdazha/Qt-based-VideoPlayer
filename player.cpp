#include "player.h"

#include <QAudioProbe>
#include <QMediaMetaData>
#include <QMediaPlaylist>
#include <QMediaService>
#include <QVideoProbe>
#include <QtWidgets>
#include <iostream>
using namespace std;

#include "absolutesetstyle.h"
#include "playlistdelegate.h"

Player::Player(QWidget *parent) : QWidget(parent), videoWidget(0), slider(0), colorDialog(0) {
    player = new QMediaPlayer(this);
    // Owned by the Player
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
    player->setNotifyInterval(20);

    // set the position of the player
    this->setGeometry(500,300,1000,600);
    this->setMinimumSize(650,450);

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, &QMediaPlayer::currentMediaChanged, this, &Player::currentMediaChanged);
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this,
            SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
    connect(player, &QMediaPlayer::stateChanged, this, &Player::stateChanged);

    videoWidget = new VideoWidget(this);
    player->setVideoOutput(videoWidget);

    playlistModel = new PlaylistModel(this);
    playlistModel->setPlaylist(playlist);

    playlistView = new QListView(this);
    playlistView->setItemDelegate(new PlaylistDelegate);
    playlistView->setModel(playlistModel);
    playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));
    connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, player->duration());
    slider->setStyle(new AbsoluteSetStyle(slider->style()));

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    labelDuration = new QLabel(this);

//    openButton = new QPushButton(tr("Open"), this);
    openButton = new QPushButton(this);
    openButton->setIcon(QIcon(":/add.png"));
    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

//    removeButton = new QPushButton(tr("Remove"), this);
    removeButton = new QPushButton(this);
    removeButton->setIcon(QIcon(":/delete.png"));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeSelected()));

    fullScreenButton = new QPushButton(tr("FullScreen"), this);
    fullScreenButton->setCheckable(true);

    initLayout();
}

Player::~Player() {}

PlayerControls *Player::initControls() {
    PlayerControls *controls = new PlayerControls(this);
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());

    connect(controls, SIGNAL(play()), player, SLOT(play()));
    connect(controls, SIGNAL(pause()), player, SLOT(pause()));
    connect(controls, SIGNAL(stop()), player, SLOT(stop()));
    connect(controls, SIGNAL(next()), playlist, SLOT(next()));
    connect(controls, SIGNAL(previous()), this, SLOT(previousClicked()));
    connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
    connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));
    connect(controls, SIGNAL(changeRate(qreal)), player, SLOT(setPlaybackRate(qreal)));

    connect(controls, SIGNAL(forward()),this, SLOT(goForward()));
    connect(controls, SIGNAL(back()),this, SLOT(goBack()));

    connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls,
            SLOT(setState(QMediaPlayer::State)));
    connect(player, SIGNAL(volumeChanged(int)), controls, SLOT(setVolume(int)));
    connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));
    return controls;
}

void Player::initLayout() {

    QWidget *listWindow = new QWidget();
    QWidget *inferiorWindow = new QWidget();
    QWidget *upperWindow = new QWidget();
    QBoxLayout *listLayout = new QVBoxLayout;



    QPalette pal(inferiorWindow->palette());

    pal.setColor(QPalette::Background, Qt::white);
    inferiorWindow->setAutoFillBackground(true);
    inferiorWindow->setPalette(pal);

    QBoxLayout *inferiorLayout = new QHBoxLayout;
    QBoxLayout *upperLayout = new QHBoxLayout;

    inferiorLayout->setMargin(0);
    listLayout->setMargin(0);

    QPushButton *test = new QPushButton("test");
    test->setIcon(QIcon(":/tag.png"));

    videoAmount = new QLabel(this);
    int videoAmountNumber = playlistView->model()->rowCount();
    char videoAmountChar[20];
    string videoAmountString = "Total " + to_string(videoAmountNumber) + " videos";
    strcpy(videoAmountChar,videoAmountString.c_str());
    videoAmount->setText(videoAmountChar);

    upperLayout->addWidget(test);
    upperWindow->setLayout(upperLayout);

    inferiorLayout->addWidget(videoAmount);
    inferiorLayout->addWidget(openButton);
    inferiorLayout->addWidget(removeButton);
    inferiorWindow->setLayout(inferiorLayout);


    listLayout->addWidget(upperWindow,1);
    listLayout->addWidget(playlistView,8);
    listLayout->addWidget(inferiorWindow,1);
    listWindow->setLayout(listLayout);

    // Top layout
    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(videoWidget, 3);
    displayLayout->addWidget(listWindow, 1);




    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(initControls());
    controlLayout->addStretch(1);
    controlLayout->addWidget(fullScreenButton);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);
    hLayout->addWidget(labelDuration);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(displayLayout, 2);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);

    setLayout(layout);
}

bool Player::isPlayerAvailable() const {
    return player->isAvailable();
}

void Player::open() {
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    fileDialog.setMimeTypeFilters(player->supportedMimeTypes());
    if (fileDialog.exec() == QDialog::Accepted) addToPlaylist(fileDialog.selectedUrls());
    int videoAmountNumber = playlistView->model()->rowCount();
    char videoAmountChar[20];
    string videoAmountString = "Total " + to_string(videoAmountNumber) + " videos";
    strcpy(videoAmountChar,videoAmountString.c_str());
    videoAmount->setText(videoAmountChar);
}

void Player::addToPlaylist(const QList<QUrl> urls) {
    foreach (const QUrl &url, urls) { playlist->addMedia(url); }
}

void Player::goForward() {
    player->setPosition(player->position()+15000);
}

void Player::goBack() {
    player->setPosition(player->position()-15000);
}

void Player::removeSelected() {
    auto current = playlistView->currentIndex();
    if (current.isValid()) {
        playlist->removeMedia(current.row());
    }
    int videoAmountNumber = playlistView->model()->rowCount();
    char videoAmountChar[20];
    string videoAmountString = "Total " + to_string(videoAmountNumber) + " videos";
    strcpy(videoAmountChar,videoAmountString.c_str());
    videoAmount->setText(videoAmountChar);
}

void Player::durationChanged(qint64 duration) {
    this->duration = duration;
    slider->setMaximum(duration);
}

void Player::positionChanged(qint64 progress) {
    if (!slider->isSliderDown()) {
        slider->setValue(progress);
    }
    updateDurationInfo(progress);
}

void Player::currentMediaChanged(const QMediaContent &media) {
    if (!media.isNull()) {
        auto url = media.canonicalRequest().url().path();
        setTrackInfo(QFileInfo(url).fileName());
    }
}

void Player::previousClicked() {
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if (player->position() <= 5)
        playlist->previous();
    else
        player->setPosition(0);
}

void Player::jump(const QModelIndex &index) {
    if (index.isValid()) {
        playlist->setCurrentIndex(index.row());
        player->play();
    }
}

void Player::playlistPositionChanged(int currentItem) {
    playlistView->setCurrentIndex(playlistModel->index(currentItem, 0));
}

void Player::seek(int seconds) {
    player->setPosition(seconds);
}

void Player::statusChanged(QMediaPlayer::MediaStatus status) {
    handleCursor(status);

    // handle status message
    switch (status) {
        case QMediaPlayer::UnknownMediaStatus:
        case QMediaPlayer::NoMedia:
        case QMediaPlayer::LoadedMedia:
        case QMediaPlayer::BufferingMedia:
        case QMediaPlayer::BufferedMedia:
            setStatusInfo(QString());
            break;
        case QMediaPlayer::LoadingMedia:
            setStatusInfo(tr("Loading..."));
            break;
        case QMediaPlayer::StalledMedia:
            setStatusInfo(tr("Media Stalled"));
            break;
        case QMediaPlayer::EndOfMedia:
            QApplication::alert(this);
            break;
        case QMediaPlayer::InvalidMedia:
            displayErrorMessage();
            break;
    }
}

void Player::stateChanged(QMediaPlayer::State state) {}

void Player::handleCursor(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::LoadingMedia || status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
}

void Player::bufferingProgress(int progress) {
    setStatusInfo(tr("Buffering %4%").arg(progress));
}

void Player::videoAvailableChanged(bool available) {
    if (!available) {
        disconnect(fullScreenButton, SIGNAL(clicked(bool)), videoWidget, SLOT(setFullScreen(bool)));
        disconnect(videoWidget, SIGNAL(fullScreenChanged(bool)), fullScreenButton,
                   SLOT(setChecked(bool)));
        videoWidget->setFullScreen(false);
    } else {
        connect(fullScreenButton, SIGNAL(clicked(bool)), videoWidget, SLOT(setFullScreen(bool)));
        connect(videoWidget, SIGNAL(fullScreenChanged(bool)), fullScreenButton,
                SLOT(setChecked(bool)));

        if (fullScreenButton->isChecked()) videoWidget->setFullScreen(true);
    }
}

void Player::setTrackInfo(const QString &info) {
    trackInfo = info;
    updateWindowTitle();
}

void Player::setStatusInfo(const QString &info) {
    statusInfo = info;
    updateWindowTitle();
}

void Player::updateWindowTitle() {
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2 - Tomeo").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(QString("%1 - Tomeo").arg(trackInfo));
}

void Player::displayErrorMessage() {
    setStatusInfo(player->errorString());
}

void Player::updateDurationInfo(qint64 currentInfo) {
    QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo / 3600 / 1000) % 60, (currentInfo / 60 / 1000) % 60,
                          currentInfo / 1000 % 60, (currentInfo) % 1000);
        QTime totalTime((duration / 3600 / 1000) % 60, (duration / 60 / 1000) % 60,
                        duration / 1000 % 60, (duration) % 1000);
        QString format = "mm:ss";
        if (duration > 3600) format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    labelDuration->setText(tStr);
}
