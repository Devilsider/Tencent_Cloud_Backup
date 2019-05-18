#include <stdio.h>
#include <stdlib.h>
#define len 10
int shell(int arr[],int arr_len){
	int gap;
	int temp;
	int i,j;
	for(int gap=(arr_len>>1);gap>0;gap=gap>>1){
		for(i=gap;i<arr_len;++i){
			temp=arr[i];
			for(j=i-gap;j>=0&&arr[j]>temp;j-=gap){
				arr[j+gap]=arr[j];
			}
			arr[j+gap]=temp;
		}
	}
	return 0;
}
int main(){
	int arr[len]={346,3423,534,6,471,324375,485,68,9675436,32463};
	shell(arr,len);
	for(int idx=0;idx<len;++idx){
		printf("%d\n",arr[idx]);
	}
	return 0;
}
