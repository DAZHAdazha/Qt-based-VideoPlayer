//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <iostream>

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
//    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
    TheButtonInfo* i = & infos -> at (count++ % infos->size());
//    cout<<rand() % infos->size()<<endl;
//    cout<<infos->size()<<endl;
//    cout<<count % infos->size()<<endl;
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    int videoLength = this->metaData("Duration").toInt();
    if(videoLength!=0){
       this->videoSlider->setMaximum(videoLength);
        this->videoSlider->setMinimum(0);
    }
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}

void ThePlayer::setVideo(int position){
    this->setPosition(position);
}

void ThePlayer::mediaChanged(bool status){
    int videoLength = this->metaData("Duration").toInt();
    if(videoLength!=0){
       this->videoSlider->setMaximum(videoLength);
        this->videoSlider->setMinimum(0);
        this->videoSlider->setValue(0);
    }
}
