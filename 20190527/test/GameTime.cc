#include "GameTime.h"

namespace warcraft{

pthread_once_t GameTime::_once=PTHREAD_ONCE_INIT;
GameTime * GameTime::_pInstance=getInstance();

GameTime * GameTime::getInstance(){
    pthread_once(&_once,init);
    return _pInstance;
}

void GameTime::init(){
    _pInstance=new GameTime();
    ::atexit(destroy);
}

void GameTime::destroy(){
    if(_pInstance){
        delete _pInstance;
    }
}

void GameTime::updateTime(){
    ++_hour;
    _hour%=24;
}

void GameTime::showTime()const{
    printf("%03lu",_hour);
}
}
