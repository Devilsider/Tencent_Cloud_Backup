#include "warrior.h"
#include "head_quarters.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using std::cout;
using std::cin;
using std::endl;
using std::string;

GameTime * GameTime::_pInstance=NULL;
pthread_once_t GameTime::_once=PTHREAD_ONCE_INIT;

void HeadQuarters::CreateIceman(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    map<int,string> wm;
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return ;
    }
    /* ++numId; */
    weapon=numId%3;
    Iceman iceman(numId,color,wLife,weapon);
    int icemanNum=getIceman();
    ++icemanNum;
    setIceman(icemanNum);
    string colorS;
    if(0==color){
        colorS="red";
    }
    if(1==color){
        colorS="blue";
    }
    wm=getWeaponMap();
    cout<<getTime()<<" "<<colorS<<" Iceman  "<<numId<<" born with strength "<<wLife<<","<<icemanNum
             <<" iceman in "<<colorS<<" headquarter."<<endl
             <<"it has a "<<wm[weapon]<<endl;
}
void HeadQuarters::CreateLion(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return ;
    }
    /* ++numId; */
    weapon=numId%3;
    int loyal=M;
    Lion lion(numId,color,wLife,weapon);
    lion.setloyalty(loyal);
    int lionNum=getIceman();
    ++lionNum;
    setLion(lionNum);
    string colorS;
    if(0==color){
        colorS="red";
    }
    if(1==color){
        colorS="blue";
    }
    cout<<getTime()<<" "<<colorS<<" Lion  "<<numId<<" born with strength "<<wLife<<","<<getLion()
        <<" Lion in "<<colorS<<" headquarter."<<endl
        <<"it's loyalty is "<<lion.getloyalty()<<endl;
}
void HeadQuarters::CreateDragon(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    map<int,string> wm;
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return ;
    }
    /* ++numId; */
    weapon=numId%3;
    double mor; 
    int dragonNum=getDragon();
    mor=M/wLife;
    ++dragonNum;
    Dragon dragon(numId,color,wLife,weapon,mor);
    setDragon(dragonNum);
    string colorS;
    if(0==color){
        colorS="red";
    }
    if(1==color){
        colorS="blue";
    }
    wm=getWeaponMap();
    cout<<getTime()<<" "<<colorS<<" Dragon  "<<numId<<" born with strength "<<wLife<<","<<getDragon()
        <<" Dragon in "<<colorS<<" headquarter."<<endl
        <<" Dragon has a "<<wm[weapon]<<" , the morale is "<<dragon.getMorale()<<endl;
}
void HeadQuarters::CreateNinja(int &M,int &wLife,int &numId,int &color){
    vector<int> weapon;
    map<int , string> wm; 
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return ;
    }
    /* ++numId; */
    weapon.push_back(numId%3);
    weapon.push_back((numId+1)%3);
    int ninjaNum=getNinja();
    ++ninjaNum;
    Ninja ninja(numId,color,wLife,weapon);
    setNinja(ninjaNum);
    string colorS;
    if(0==color){
        colorS="red";
    }
    if(1==color){
        colorS="blue";
    }
    wm=getWeaponMap();
    cout<<getTime()<<" "<<colorS<<" Ninja  "<<numId<<" born with strength "<<wLife<<","<<getNinja()
                <<" Ninja in "<<colorS<<" headquarter."<<endl
                <<" Ninja has a "<<wm[weapon[0]]<<" and a "<<wm[weapon[1]]<<endl;
}
void HeadQuarters::CreateWolf(int &M,int &wLife,int &numId,int &color){
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return ;
    }
    /* ++numId; */
    int wolfNum=getWolf();
    ++wolfNum;
    setNinja(wolfNum);
    string colorS;
    if(0==color){
        colorS="red";
    }
    if(1==color){
        colorS="blue";
    }
    Wolf wolf(numId,color,wLife);
    cout<<getTime()<<" "<<colorS<<" Wolf  "<<numId<<" born with strength "<<wLife<<","<<getWolf()
        <<" Wolf in "<<colorS<<"  headquarter."<<endl;
}

void RedHeadQuarter::CreateWarrior(vector<int> &warriorLife)
{
    int M=getM();
    int numId=getNumId();
    int red=getColor();
    int wLife=0;
    int minWarriorLif=*min_element(warriorLife.begin(),warriorLife.end());

    if(M>0&&M>=minWarriorLif){
        ++numId;
        setNumId(numId);
        int type = numId%5;
        switch(type){
            case 1: 
            wLife=warriorLife[2];
            CreateIceman(M,wLife,numId,red);
            break;
            
            case 2:
            wLife=warriorLife[3];
            CreateLion(M,wLife,numId,red);
            break;
            
            case 3:
            wLife=warriorLife[4];
            CreateWolf(M,wLife,numId,red);
            break;
           
            case 4:
            wLife=warriorLife[1];
            CreateNinja(M,wLife,numId,red);
            break;
            
            case 0:
            wLife=warriorLife[0];
            CreateDragon(M,wLife,numId,red);
            break;

            default:
            break;
        }
    }
    cout<<getTime()<<" red HeadQuarters stops making warriors!"<<endl;
}
void BlueHeadQuarter::CreateWarrior(vector<int> &warriorLife)
{
    int M=getM();
    int numId=getNumId();
    int blue=getColor();
    int wLife=0;
    int minWarriorLif=*min_element(warriorLife.begin(),warriorLife.end());

    if(M>0&&M>=minWarriorLif){
        ++numId;
        setNumId(numId);
        int type = numId%5;
        switch(type){
            case 1: 
            wLife=warriorLife[3];
            CreateLion(M,wLife,numId,blue);
            break;
            
            case 2:
            wLife=warriorLife[0];
            CreateDragon(M,wLife,numId,blue);
            break;
            
            case 3:
            wLife=warriorLife[1];
            CreateNinja(M,wLife,numId,blue);
            break;
           
            case 4:
            wLife=warriorLife[2];
            CreateIceman(M,wLife,numId,blue);
            break;
            
            case 0:
            wLife=warriorLife[4];
            CreateWolf(M,wLife,numId,blue);
            break;

            default:
            break;
        }
    }
    cout<<getTime()<<" blue HeadQuarters stops making warriors!"<<endl;
}


