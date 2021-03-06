#ifndef __GATIME_H__
#define __GATIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

namespace warcraft{

class GameTime
{
public:
    static GameTime *getInstance();
    static void init();
    static void destroy();
    size_t getTime()const{
        return _hour;
    }
    void showTime()const;
    void updateTime();
private:
    GameTime(size_t hour=0)
    :_hour(hour)
    {
    }
private:
    static GameTime *_pInstance;
    static pthread_once_t _once;
    size_t _hour;
};

}
#endif
