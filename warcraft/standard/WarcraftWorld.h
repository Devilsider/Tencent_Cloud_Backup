#pragma once
#include "data_type.h"
#include "City.h"
#include "Headquarters.h"
#include <iostream>
namespace warcraft{

class WarcraftWorld
{
public:
    explicit 
    WarcraftWorld() 
    :_redHeadquarters(NULL)
     ,_blueHeadquarters(NULL)
    {
        init();
    }
    void start()//游戏开始
    {
        while(1){
            createWarrior();
            if(!warriorMarch()){
                break;
            }
            cityProduceElements();
            takeCityElements();
            battle();
            headquartersReportElements();
        }

    }

    template<typename Iterator>
        void setRedWarriorCreatingOrder(Iterator beg,Iterator end);

    template<typename Iterator>
        void setBlueWarriorCreatingOrder(Iterator beg,Iterator end);
    ~WarcraftWorld()
    {
        if(_redHeadquarters){
            delete _redHeadquarters;
        }
        if(_blueHeadquarters){
            delete _blueHeadquarters;
        }
    }

private:
    void init();
    //---------------事件begin------------------
    void createWarrior();//整点创建武士
    bool warriorMarch();//第10分：武士行军
    void cityProduceElements();//第20分，城市生产生命元
    void takeCityElements();//第30分，武士取走城市中的生命元
    void battle();//第40分，战斗
    void headquartersReportElements();//第50分，司令部报告情况
    //-----------------事件end
    
    bool createWarrior(Headquarters *);//某个司令部开始创建武士
    void warriorMarch(Headquarters * headquarters);//某个司令部的武士行军
    
    bool checkRedHeadquartersBeTaken();//判断红军司令部是否被占领
    bool checkBlueHeadquartersBeTaken();//判断蓝军司令部是否被占领


private:
    Headquarters * _redHeadquarters;//红色司令部
    Headquarters * _blueHeadquarters;//蓝色司令部
    vector<City> _cities;//所有城市,其中0代表红色司令部，size-1代表蓝色司令部
};
template<typename Iterator>
    void WarcraftWorld::setRedWarriorCreatingOrder(Iterator beg,Iterator end){
        _redHeadquarters->setWarriorCreatingOrder(beg,end);
    }

template<typename Iterator>
    void WarcraftWorld::setBlueWarriorCreatingOrder(Iterator beg,Iterator end){
        _blueHeadquarters->setWarriorCreatingOrder(beg,end);
    }
}//end of namespace wd;


