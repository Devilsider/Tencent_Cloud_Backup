#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T,typename Compare = std::less<T>>
class HeapSort{
public:
    HeapSort()
    {}
    HeapSort(vector<T> &arr)
    :_arr(arr)
    {}

    void heapify(int start,int end){
        int dad=start;
        int son=dad*2+1;
        while(son<end){
            if(son+1<end&&_arr[son]<_arr[son+1]){
                ++son;
            }
            if(_arr[dad]>=_arr[son]){
                return ;
            }
            else{
                swap(_arr[son],_arr[dad]);
                dad=son;
                son=dad*2+1;
            }
        }
    }

    void heapSort(){
        for(int i=(_arr.size()/2-1);i>=0;--i){
            heapify(i,_arr.size());
        }
        for(int i=_arr.size()-1;i>0;--i){
            swap(_arr[0],_arr[i]);
            heapify(0,i-1);
        }
    }
    
    void setArr(vector<T> &arr){
        _arr=arr;
    }

    void print(){
        for(auto &i:_arr){
            cout<<" "<<i;
        }
        cout<<endl;
    }
private:
    vector<T> _arr;
};


#endif
