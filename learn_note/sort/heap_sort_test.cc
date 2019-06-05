#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <iostream>
using std::swap;
using std::cout;
using std::endl;
void maxHeapify(int arr[],int start,int end){
    int dad=start;
    int son=dad*2+1;
    while(son<=end){
        if(son+1<=end&&arr[son]<arr[son+1]){
            ++son;
        }
        if(arr[dad]>arr[son]){
            return ;
        }
        else {
            swap(&arr[dad],&arr[son]);
            dad=son;
            son=dad*2+1;
        }
    }
}

void headSort(int arr[],int len){
    int i;
    for( i=len/2-1;i>=0;--i){
        maxHeapify(arr,i,len-1);
    }
    for(i=len-1;i>0;--i){
        swap(&arr[0],&arr[i]);
        maxHeapify(arr,0,i-1);
    }
}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

