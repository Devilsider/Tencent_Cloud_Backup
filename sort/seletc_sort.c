#include <stdio.h>
#include <stdlib.h>
#define len 10
int select_sort(int arr[],int arr_len){
	int temp;
	for(int i=0;i<arr_len-1;++i){
		for(int j=i+1;j<arr_len;++j){
			if(arr[i]>arr[j]){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	return 0;
}
int main(){
	int arr[len]={1,233,5325,23,66,1467,235,3425,67,34};
	select_sort(arr,len);
	for(int idx=0;idx<len;++idx){
		printf("%d\n",arr[idx]);
	}
	return 0;
}

