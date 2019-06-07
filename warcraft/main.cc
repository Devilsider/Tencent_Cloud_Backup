#include "warrior.h"
#include "head_quarters.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;

typedef  struct {
    vector<int> warriorLife;
}Data,*pData;
void * sigFunc(void *p){
    
    pData pd=(pData ) p;
    BlueHeadQuarter blueHead;
    int M=20;
    int blue=1;
    blueHead.setM(M);
    blueHead.setColor(blue);
    sleep(3);
    /* for(auto &i:pd->warriorLife){ */
    /*     cout<<" sigfunc "<< i <<endl; */
    /* } */
    vector<Warrior*> blueVector;
    std::unique_ptr<vector<Warrior*>> pBlue(&blueVector);
    
    blueHead.CreateWarrior(pd->warriorLife,pBlue);
    return NULL;
}

int main()
{
    vector<int> warriorLife;
    int caseNum;
    RedHeadQuarter redHead;
    /* BlueHeadQuarter blueHead; */
    int M=20;
    int temp;
    redHead.setM(M);
    /* blueHead.setM(M); */
    int red=0;
    /* int blue=1; */
    redHead.setColor(red);
    /* blueHead.setColor(blue); */
    /* while(1){ */
        cout<<"please input data"<<endl;
        cin>>caseNum;
        for(int idx=0;idx<5;++idx){
            cin>>temp;
            warriorLife.push_back(temp);
        }
        cout<<"case "<<caseNum<<endl;
    /* } */

    pData pd;
    pd=(pData)calloc(1,sizeof(Data)); 
    pd->warriorLife=warriorLife;
    
    pthread_t pid;
    pthread_create(&pid,NULL,sigFunc,pd);
    sleep(4);
    
    vector<Warrior*> redVector;
    std::unique_ptr<vector<Warrior*>> pRed(&redVector);

    redHead.CreateWarrior(warriorLife,pRed);

    /* blueHead.CreateWarrior(warriorLife); */
    return 0;
}

