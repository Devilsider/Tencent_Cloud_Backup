#ifndef __LRUCACHE_H__
#define __LRUCACHE_H__
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <map>
using std::cout;
using std::list;
using std::endl;
using std::unordered_map;
using std::map;

class LRUCache
{
public:
    LRUCache(int capacity)
    :_capacity(capacity),_sizeOfUsingCache(0)
    {}
    int get(int key){
        if(0==_sizeOfUsingCache&&0==_capacity){//边界条件
            return -1;
        }
        auto ret=_lruCache.find(key);
        if(ret==_lruCache.end()){
            
            return -1;
        }
        else{
            //hashmap中有该节点，更新链表
            auto i=_lruCache.find(key)->second;
            --_sizeOfUsingCache;
            auto temp=std::make_pair(i->first,i->second);
            _dataList.erase(i);
            ++_sizeOfUsingCache;
            _dataList.insert(_dataList.begin(),temp);
            _lruCache.find(key)->second=_dataList.begin();
            
            return _lruCache.find(key)->second->second;
        }
    }

    void put(int key,int value){
        if(0==_sizeOfUsingCache&&0==_capacity){
            return;
        }
        if(_lruCache.find(key)==_lruCache.end()){
            //hashmap中不存在，新建一个节点，并且插入到链表中
            if(_sizeOfUsingCache<_capacity){
                //表未满
                ++_sizeOfUsingCache;
                _dataList.insert(_dataList.begin(),std::make_pair(key,value));
                _lruCache.insert(std::make_pair(key,_dataList.begin()));
            }
            else {
                //表已满，先删除最后一个
                --_sizeOfUsingCache;
            
                int tempKey=_dataList.rbegin()->first;
                _dataList.pop_back();
                _lruCache.erase(tempKey);
                ++_sizeOfUsingCache;
                _dataList.insert(_dataList.begin(),std::make_pair(key,value));
                _lruCache.insert(std::make_pair(key,_dataList.begin()));
            }
            return;
        }
        else{
            //hashmap中存在
            
                //表未满
            
                auto it=_lruCache.find(key)->second;
                --_sizeOfUsingCache;
                _dataList.erase(it);
                ++_sizeOfUsingCache;
                _dataList.insert(_dataList.begin(),std::make_pair(key,value));
                _lruCache.find(key)->second=_dataList.begin();
                return;
              
        }
    }
    void print(){
        cout<<">>>list"<<endl;
        for(auto &i:_dataList){
            cout<<" key is"<<i.first<<" value is "<<i.second;
        }
        cout<<endl;
        cout<<">>>map" <<endl;
        for(auto &i:_lruCache){
            cout<<" key="<<i.first;
        }
        cout<<endl;
    }
    ~LRUCache(){

    }
private:
    int _capacity;
    int _sizeOfUsingCache;
    unordered_map<int,list<std::pair<int,int>>::iterator> _lruCache;//存放数据
    list<std::pair<int,int>> _dataList;//模拟内存,存放capacity个数据
};

#endif
