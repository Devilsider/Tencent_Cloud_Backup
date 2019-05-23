#include "warrior.h"
#include "head_quarters.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

void RedHeadQuarter::CreateWarrior(vector<int> &warriorLife)
{
    int tempLife=0;
    int numId=0;
    int red=0;
    int wLife ;
    int weapon;
    vector <int> count;
    for(int idx=0;idx<getTime();++idx){
        while(getM()>tempLife){
            //ICEMAN init 2
            wLife=warriorLife[2];
            ++numId;
            weapon=numId%3;
            tempLife=tempLife+warriorLife[2];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[2];
                break;
            }
            Iceman iceman(numId,red,wLife,weapon);
            ++count[0];
            cout<<idx<<" red "<<" Iceman  "<<numId<<" born with strength "<<wLife<<","<<count[0]
                <<" iceman in red headquarter."<<endl
                <<"it has a "<<weapon<<endl;
            //LION INIT 3
            wLife=warriorLife[3];
            ++numId;
            weapon=numId%3;
            tempLife=tempLife+warriorLife[3];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[3];
                break;
            }
            int loyal=getM()-tempLife;
            Lion lion(numId,red,wLife,weapon);
            lion.setloyalty(loyal);
            ++count[1];
            cout<<idx<<" red "<<" Lion  "<<numId<<" born with strength "<<wLife<<","<<count[1]
                <<" Lion in red headquarter."<<endl
                <<"it's loyalty is "<<lion.getloyalty()<<endl;
            //Wolf Init 4
            wLife=warriorLife[4];
            ++numId;
            tempLife=tempLife+warriorLife[4];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[4];
                break;
            }
            Wolf wolf(numId,red,wLife);
            ++count[2];
            cout<<idx<<" red "<<" Wolf  "<<numId<<" born with strength "<<wLife<<","<<count[2]
                <<" Wolf in red headquarter."<<endl;
            //NINJA INIT 1
            wLife=warriorLife[1];
            ++numId;
            vector<int> w;
            w[0]=numId%3;
            w[1]=(numId+1)%3;
            tempLife=tempLife+warriorLife[1];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[1];
                break;
            }
            Ninja ninja(numId,red,wLife,w);
            ++count[3];
            cout<<idx<<" red "<<" Ninja  "<<numId<<" born with strength "<<wLife<<","<<count[3]
                <<" Ninja in red headquarter."<<endl
                <<" Ninja has a "<<w[0]<<" and a "<<w[1]<<endl;
            
            //Dragon INIT 0
            wLife=warriorLife[0];
            ++numId;
            weapon=numId%3; 
            double mor;
            tempLife=tempLife+warriorLife[0];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[0];
                break;
            }
            mor=(getM()-tempLife)/wLife;
            Dragon dragon(numId,red,wLife,weapon,mor);
            ++count[4];
            cout<<idx<<" red "<<" Dragon  "<<numId<<" born with strength "<<wLife<<","<<count[4]
                <<" Dragon in red headquarter."<<endl
                <<" Dragon has a "<<weapon<<" , the morale is "<<dragon.getMorale()<<endl;
        }
        //最后一次没有判定
        //for(int idx)
    }
}
void BlueHeadQuarter::CreateWarrior(vector<int> &warriorLife)
{
    int tempLife=0;
    int numId=0;
    int red=0;
    int wLife ;
    int weapon;
    vector <int> count;
    for(int idx=0;idx<getTime();++idx){
        while(getM()>tempLife){
            //LION INIT 3
            wLife=warriorLife[3];
            ++numId;
            weapon=numId%3;
            tempLife=tempLife+warriorLife[3];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[3];
                break;
            }
            int loyal=getM()-tempLife;
            Lion lion(numId,red,wLife,weapon);
            lion.setloyalty(loyal);
            ++count[0];
            cout<<idx<<" red "<<" Lion  "<<numId<<" born with strength "<<wLife<<","<<count[0]
                <<" Lion in red headquarter."<<endl
                <<"it's loyalty is "<<lion.getloyalty()<<endl;
            //Dragon INIT 0
            wLife=warriorLife[0];
            ++numId;
            weapon=numId%3; 
            double mor;
            tempLife=tempLife+warriorLife[0];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[0];
                break;
            }
            mor=(getM()-tempLife)/wLife;
            Dragon dragon(numId,red,wLife,weapon,mor);
            ++count[1];
            cout<<idx<<" red "<<" Dragon  "<<numId<<" born with strength "<<wLife<<","<<count[1]
                <<" Dragon in red headquarter."<<endl
                <<" Dragon has a "<<weapon<<" , the morale is "<<dragon.getMorale()<<endl;
            //NINJA INIT 1
            wLife=warriorLife[1];
            ++numId;
            vector<int> w;
            w[0]=numId%3;
            w[1]=(numId+1)%3;
            tempLife=tempLife+warriorLife[1];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[1];
                break;
            }
            Ninja ninja(numId,red,wLife,w);
            ++count[2];
            cout<<idx<<" red "<<" Ninja  "<<numId<<" born with strength "<<wLife<<","<<count[2]
                <<" Ninja in red headquarter."<<endl
                <<" Ninja has a "<<w[0]<<" and a "<<w[1]<<endl;
            //ICEMAN init 2
            wLife=warriorLife[2];
            ++numId;
            weapon=numId%3;
            tempLife=tempLife+warriorLife[2];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[2];
                break;
            }
            Iceman iceman(numId,red,wLife,weapon);
            ++count[3];
            cout<<idx<<" red "<<" Iceman  "<<numId<<" born with strength "<<wLife<<","<<count[3]
                <<" iceman in red headquarter."<<endl
                <<"it has a "<<weapon<<endl;
            //Wolf Init 4
            wLife=warriorLife[4];
            ++numId;
            tempLife=tempLife+warriorLife[4];
            if(getM()<tempLife) {
                tempLife=tempLife-warriorLife[4];
                break;
            }
            Wolf wolf(numId,red,wLife);
            ++count[4];
            cout<<idx<<" red "<<" Wolf  "<<numId<<" born with strength "<<wLife<<","<<count[4]
                <<" Wolf in red headquarter."<<endl;
            }
        //最后一次没有判定
    }
}
int main()
{
    vector<int> warriorLife;
    int caseNum;
    RedHeadQuarter red;
    BlueHeadQuarter blue;
    while(1){
        cout<<"please input data"<<endl;
        cin>>caseNum;
        for(int idx=0;idx<5;++idx){
            cin>>warriorLife[idx];
        }
        cout<<"case "<<caseNum;
    }
    return 0;
}

