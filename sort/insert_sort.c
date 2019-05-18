#include <stdio.h>
#include <stdlib.h>
#define len 10
int insert_sort(int arr[],int arr_len){
	for(int i=1;i<arr_len;++i){
		int temp=arr[i];
		int j;
		for(j=i-1;j>=0&&arr[j]>temp;--j){
			arr[j+1]=arr[j];
		}
		arr[j+1]=temp;
	}
	return 0;
}
int main(){
	int arr[len]={1,2,21321,4535,364,47,658,679,676432,21312};
	insert_sort(arr,len);
	for(int idx=0;idx<len;++idx){
		printf("%d\n",arr[idx]);
	}
	return 0;
}

