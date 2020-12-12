#include "playercontrols.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QStyle>
#include <QToolButton>

PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent), playerState(QMediaPlayer::StoppedState), playerMuted(false) {
    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

    nextButton = new QToolButton(this);
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));

    previousButton = new QToolButton(this);
    previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));

    muteButton = new QToolButton(this);
    muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderValueChanged()));

    rateBox = new QComboBox(this);
    rateBox->addItem("0.25x", QVariant(0.25));
    rateBox->addItem("0.5x", QVariant(0.5));
    rateBox->addItem("0.75x", QVariant(0.75));
    rateBox->addItem("1.0x", QVariant(1.0));
    rateBox->addItem("1.25x", QVariant(1.25));
    rateBox->addItem("1.5x", QVariant(1.5));
    rateBox->addItem("1.75x", QVariant(1.75));
    rateBox->addItem("2.0x", QVariant(2.0));
    rateBox->setCurrentIndex(3);
    connect(rateBox, SIGNAL(activated(int)), SLOT(updateRate()));

    initLayout();
}

void PlayerControls::initLayout() {
    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(playButton);
    layout->addWidget(previousButton);
    layout->addWidget(stopButton);
    layout->addWidget(nextButton);
    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    layout->addWidget(rateBox);
    setLayout(layout);
}

QMediaPlayer::State PlayerControls::state() const {
    return playerState;
}

void PlayerControls::setState(QMediaPlayer::State state) {
    if (state != playerState) {
        playerState = state;

        switch (state) {
            case QMediaPlayer::StoppedState:
                stopButton->setEnabled(false);
                playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
            case QMediaPlayer::PlayingState:
                stopButton->setEnabled(true);
                playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                break;
            case QMediaPlayer::PausedState:
                stopButton->setEnabled(true);
                playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
        }
    }
}

int PlayerControls::volume() const {
    qreal linearVolume =
        QAudio::convertVolume(volumeSlider->value() / qreal(100), QAudio::LogarithmicVolumeScale,
                              QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
}

void PlayerControls::setVolume(int volume) {
    qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100), QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    volumeSlider->setValue(qRound(logarithmicVolume * 100));
}

bool PlayerControls::isMuted() const {
    return playerMuted;
}

void PlayerControls::setMuted(bool muted) {
    if (muted != playerMuted) {
        playerMuted = muted;

        muteButton->setIcon(
            style()->standardIcon(muted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
    }
}

void PlayerControls::playClicked() {
    switch (playerState) {
        case QMediaPlayer::StoppedState:
        case QMediaPlayer::PausedState:
            emit play();
            break;
        case QMediaPlayer::PlayingState:
            emit pause();
            break;
    }
}

void PlayerControls::muteClicked() {
    emit changeMuting(!playerMuted);
}

qreal PlayerControls::playbackRate() const {
    return rateBox->itemData(rateBox->currentIndex()).toDouble();
}

void PlayerControls::setPlaybackRate(float rate) {
    for (int i = 0; i < rateBox->count(); ++i) {
        if (qFuzzyCompare(rate, float(rateBox->itemData(i).toDouble()))) {
            rateBox->setCurrentIndex(i);
            return;
        }
    }

    rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
    rateBox->setCurrentIndex(rateBox->count() - 1);
}

void PlayerControls::updateRate() {
    emit changeRate(playbackRate());
}

void PlayerControls::onVolumeSliderValueChanged() {
    emit changeVolume(volume());
}
