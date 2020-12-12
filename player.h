#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

#include "playercontrols.h"
#include "playlistmodel.h"
#include "videowidget.h"

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoWidget;
QT_END_NAMESPACE

class PlaylistModel;

class Player : public QWidget {
    Q_OBJECT

   public:
    Player(QWidget *parent = 0);
    ~Player();

    bool isPlayerAvailable() const;

    void addToPlaylist(const QList<QUrl> urls);

   signals:
    void fullScreenChanged(bool fullScreen);

   private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void currentMediaChanged(const QMediaContent &media);

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void removeSelected();
    void playlistPositionChanged(int);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

   private:
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void updateWindowTitle();
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    // Initializes layouts
    void initLayout();
    PlayerControls *initControls();

    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    VideoWidget *videoWidget;
    QSlider *slider;
    QLabel *labelDuration;
    QPushButton *fullScreenButton;
    QPushButton *colorButton;
    QDialog *colorDialog;
    QAbstractButton *openButton;
    QAbstractButton *removeButton;

    PlaylistModel *playlistModel;
    QAbstractItemView *playlistView;
    QString trackInfo;
    QString statusInfo;
    qint64 duration;
};

#endif  // PLAYER_H
