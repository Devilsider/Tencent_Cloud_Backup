#include<stdio.h>
#include<stdlib.h>
void select_sort(int arr[],int len){
	int i,j,temp;
	i=0;
	j=0;
	for(i=0;i<len;++i){
		for(j=i;j<len;++j){
			if(arr[j]<arr[i]){
			temp=arr[j];
			arr[j]=arr[i];
			arr[i]=temp;
			}	
		}
	}
}
void main(){
	int arr[10]={11,3,56,2,6,8,1,7,9,7};
	select_sort(arr,10);
	for(int idx=0;idx<10;++idx){
		printf("the num is %d\n",arr[idx]);
	}
}

