//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>
#include <QSlider>

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    vector<TheButtonInfo>* infos;
    vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;
    long count = 0;


public:

    QSlider* volumeSlider;
    QSlider* videoSlider;
    QPushButton *playButton;
    QPushButton *stopButton;

    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        connect (this, SIGNAL (metaDataAvailableChanged(bool)), this, SLOT (mediaChanged(bool)) );

        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method

        this->volumeSlider = new QSlider(Qt::Vertical);
        this->videoSlider = new QSlider(Qt::Horizontal);
        this->playButton = new QPushButton("Play");
        this->stopButton = new QPushButton("Stop");

        // use slider to control the volume here
        connect(this->volumeSlider,SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
        connect(this->playButton, SIGNAL(clicked(bool)), this, SLOT(play()));
        connect(this->stopButton, SIGNAL(clicked(bool)), this, SLOT(pause()));
        connect(this->videoSlider,SIGNAL(valueChanged(int)),this,SLOT(setVideo(int)));
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);  
private slots:

    // change the image and video for one button every one second
    void shuffle();

    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void setVideo(int position);
    void mediaChanged(bool status);
};

#endif //CW2_THE_PLAYER_H
