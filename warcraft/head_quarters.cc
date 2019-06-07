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

Iceman * HeadQuarters::CreateIceman(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    map<int,string> wm;
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return NULL;
    }
    /* ++numId; */
    weapon=numId%3;
    /* Iceman iceman(numId,color,wLife,weapon); */
    Iceman *iceman = new Iceman(numId,color,wLife,weapon);
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
    return iceman;
}
Lion *HeadQuarters::CreateLion(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return NULL;
    }
    /* ++numId; */
    weapon=numId%3;
    int loyal=M;
    /* Lion lion(numId,color,wLife,weapon); */
    Lion *lion=new Lion(numId,color,wLife,weapon);
    lion->setloyalty(loyal);
    int lionNum=getLion();
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
        <<"it's loyalty is "<<lion->getloyalty()<<endl;
    return lion;
}
Dragon* HeadQuarters::CreateDragon(int &M,int &wLife,int &numId,int &color){
    int weapon; 
    map<int,string> wm;
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return NULL;
    }
    /* ++numId; */
    weapon=numId%3;
    double mor; 
    int dragonNum=getDragon();
    mor=M/wLife;
    ++dragonNum;
    /* Dragon dragon(numId,color,wLife,weapon,mor); */
    Dragon *dragon=new Dragon(numId,color,wLife,weapon,mor);
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
        <<" Dragon has a "<<wm[weapon]<<" , the morale is "<<dragon->getMorale()<<endl;
    return dragon;
}
Ninja* HeadQuarters::CreateNinja(int &M,int &wLife,int &numId,int &color){
    vector<int> weapon;
    map<int , string> wm; 
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return NULL;
    }
    /* ++numId; */
    weapon.push_back(numId%3);
    weapon.push_back((numId+1)%3);
    int ninjaNum=getNinja();
    ++ninjaNum;
    Ninja *ninja = new Ninja(numId,color,wLife,weapon);
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
    return ninja;
}
Wolf *HeadQuarters::CreateWolf(int &M,int &wLife,int &numId,int &color){
    M=M-wLife;
    if(M<0){
        //生命元不够
        M=M+wLife;
        return NULL;
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
    Wolf *wolf = new Wolf(numId,color,wLife);
    cout<<getTime()<<" "<<colorS<<" Wolf  "<<numId<<" born with strength "<<wLife<<","<<getWolf()
        <<" Wolf in "<<colorS<<"  headquarter."<<endl;
    return wolf;
}

void RedHeadQuarter::CreateWarrior(vector<int> &warriorLife,
                                   std::unique_ptr<vector<Warrior*>> &warrior)
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
            warrior->push_back(CreateIceman(M,wLife,numId,red));
            break;
            
            case 2:
            wLife=warriorLife[3];
            warrior->push_back(CreateLion(M,wLife,numId,red));
            break;
            
            case 3:
            wLife=warriorLife[4];
            warrior->push_back(CreateWolf(M,wLife,numId,red));
            break;
           
            case 4:
            wLife=warriorLife[1];
            warrior->push_back(CreateNinja(M,wLife,numId,red));
            break;
            
            case 0:
            wLife=warriorLife[0];
            warrior->push_back(CreateDragon(M,wLife,numId,red));
            break;

            default:
            break;
        }
    }
    cout<<getTime()<<" red HeadQuarters stops making warriors!"<<endl;
}
void BlueHeadQuarter::CreateWarrior(vector<int> &warriorLife,
                                    std::unique_ptr<vector<Warrior*>> &warrior)
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
            warrior->push_back(CreateLion(M,wLife,numId,blue));
            break;
            
            case 2:
            wLife=warriorLife[0];
            warrior->push_back(CreateDragon(M,wLife,numId,blue));
            break;
            
            case 3:
            wLife=warriorLife[1];
            warrior->push_back(CreateNinja(M,wLife,numId,blue));
            break;
           
            case 4:
            wLife=warriorLife[2];
            warrior->push_back(CreateIceman(M,wLife,numId,blue));
            break;
            
            case 0:
            wLife=warriorLife[4];
            warrior->push_back(CreateWolf(M,wLife,numId,blue));
            break;

            default:
            break;
        }
    }
    cout<<getTime()<<" blue HeadQuarters stops making warriors!"<<endl;
}


