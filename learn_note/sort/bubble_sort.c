#include <stdio.h>
#include <stdlib.h>
#define len 10
int bubble_sort(int arr[],int arr_len){
	int temp;
	for(int i=0;i<arr_len-1;++i){
		for(int j=0;j<arr_len-1-i;++j){
			if(arr[j]>arr[j+1]){
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	return 0;
}
int main(){
	int arr[len]={132,1,213213,13,4325,6777,789,68,934,693};
	bubble_sort(arr,len);
	for(int idx=0;idx<len;++idx){
		printf("%d\n",arr[idx]);
	}
}

