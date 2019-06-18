#include "MyTask.h"

#include <sstream>
#include <iostream>
using std::stringstream;
using std::cout;
using std::endl;

namespace  wd
{
MyTask::MyTask(const string &msg,const TcpConnectionPtr &conn)
:_query(msg)
,_conn(conn)
{}

int MyTask::calcDistance(string &rhs)
{
    //初始化二维数组，用于存储动态规划中的中间数值
        string s1=_query;
        string s2=rhs;

        int len1=(int)s1.size();
        int len2=(int)s2.size();

        vector<vector<int>> martix(len1+1,vector<int>(len2+1,0));
        for(int j=0;j<len2+1;++j)
        {
            martix[0][j]=j;
        }
        for(int i=0;i<len1+1;++i)
        {
            martix[i][0]=i;
        }
        for(int i=1;i<len1+1;++i)
        {
            for(int j=1;j<len2+1;++j)
            {
                    int f;
                    f = (s1[i-1]==s2[j-1])?0:1;
                    martix[i][j]=minOfThree(martix[i-1][j]+1,martix[i][j-1]+1,martix[i-1][j-1]+f);
            }
        }
        return martix[len1][len2];
}

int MyTask::minOfThree(int t1,int t2,int t3)
{
    int min;
    min = t1>t2?t2:t1;
    min = min>t3?t3:min;
    return min;
}

void MyTask::process()
{
    //1.得到了索引表的指针_pindex
    //2.将单词_query与索引表中单词比对，
    //求出编辑距离，将结果存储到结构体
    //MyResult中。
    //3.设置优先级队列的比较条件，按照
    //编辑距离来比较，若编辑距离相等，则按照频次来比较，
    //频次高的在前面
    //4.取前k个单词，并将其封装成jason文件，memcpy给ms，再
    //使用sendLoop(msg),延缓到IO线程发送

    /* cout<<" _pindex = "<<_pindex<<endl; */
    stringstream ss;
    string tmp;
    
    vector<std::pair<string,int>> &dict = _pindex->getDict();
    unordered_map<string,set<int>> &index = _pindex->getIndex();
    BitMap myBitMap(10000);
    cout<<" dict.size()= " <<dict.size()<<endl;
    cout<<" index.size()= "<<index.size()<<endl;
    
    for(auto &i:index)
    {
        cout<<i.first<<": ";
        for(auto &j:i.second)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }

    cout<<"_query= "<<_query<<endl;

    for(auto &ch:_query)
    {
        //ch转换成string
        ss.clear();
        ss.str("");
        tmp.clear();
        tmp="";
        ss<<ch;
        tmp=ss.str();
        /* cout<<" ch  = "<<tmp<<endl; */
        auto indexSet = index.find(tmp);
        if(indexSet==index.end()){
            cout<<"11"<<endl;
            return;
        }
        /* for(auto &i:indexSet) */
        /* { */
        /*     cout<<" "<<i<<endl; */
        /* } */
        int count=0;
        /* for(auto &n:indexSet) */
        /* { */
        /*     /1* if(n>100000){ *1/ */
        /*      cout<<"count=  "<<count<<" n = "<<n<<endl; */
        /*      /1* } *1/ */
        /*     ++count; */
        /* } */
        /* exit(0); */
        for(auto &idx:indexSet->second)
        {
            /* cout<<"4"<<endl; */
            cout<<" idx = "<<idx<<endl;
            /* cout<<" count = "<<count<<endl; */
            /* ++count; */
            //使用BitMap去重
            if(!myBitMap.test(idx))
            {   //未计算
                /* cout<<"5"<<endl; */
                int dist = calcDistance(dict[idx].first);
                MyResult node ;
                node._iDist=dist;
                node._iFeq=dict[idx].second;
                node._word=dict[idx].first;

                /* cout<<"count =  "<<count<<", word = "<<node._word */
                /*     <<",dist = "<<node._iDist<<",freq= "<<node._iFeq<<endl; */
                /* ++count; */
                _que.push(node);
                //计算该位后将其置为1
                myBitMap.set(idx);
            }
            cout<<" count = "<<count<<endl;
            ++count;
        }

    }
    cout<<"---------------------"<<endl;
    cout<<" dict.size()= " <<dict.size()<<endl;
    cout<<" index.size()= "<<index.size()<<endl;
    
    cout<<" que.size() =  " <<_que.size()<<endl;
    cout<<"1111"<<endl;
    string res(_que.top()._word);
    cout<<"2222"<<endl;
    cout<<" the best match is : "<<res<<endl;
    _conn->sendInLoop(res);
}

}//end of wd

