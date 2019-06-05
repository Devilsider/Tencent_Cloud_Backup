#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T,typename Compare = std::less<T>>
class HeapSort{
public:
    HeapSort()
    {}
    HeapSort(T &arr)
    :_arr(arr)
    {}
    void Heapify(vector<T> &arr,int start,int end){
        int dad=start;
        int son=dad*2+1;

        while(son<end){
            if(son+1<=end&&arr[son]<arr[son+1]){
                ++son;
            }
            if(arr[dad]>=arr[son]){
                return ;
            }
            else {
                swap(arr[son],arr[dad]);
                dad=son;
                son=dad*2+1;
            }
        }
    }

    void sort(){
        int len= _arr.size();
        /* size_t start = 0; */
        /* size_t end = len-1; */

        for(int i=(int)len/2-1;i>=0;--i){
            Heapify(_arr,i,len);
        }
        for(int i=(int)len-1;i>0;--i){
            swap(_arr[0],_arr[i]);
            Heapify(_arr,0,i-1);
        }
    }

    void print(){
        for(auto &i:_arr){
            cout<<" "<<i;
        }
        cout<<endl;
    }
    void setArr(vector<T> arr){
        _arr=arr;
    }
private:
    vector<T> _arr;
};


int  main(){
    vector<int> arr={23,5,6,788,2312,87568,123,6,88,9,123};
    HeapSort<int> hs;
    hs.setArr(arr);

    hs.sort();
    hs.print();
    return 0;
}


