#include <stdio.h>
#include <stdlib.h>
#define max_len 10
int maxHeapify(int arr[],int start,int end){
	int dad=start;
	int son=(dad<<1)+1;
	while(son<=end){
		if(son+1<=end&&arr[son]<arr[son+1]){
			++son;
		}
		if(arr[dad]>=arr[son]){
			return 0;
		}
		else{
			int temp = arr[son];
			arr[son]=arr[dad];
			arr[dad]=temp;
			dad=son;
			son=(dad<<1)+1;
		}
	}
	return 0;
}
int heap_sort(int arr[],int len){
	for(int idx=(len>>1)-1;idx>=0;--idx){
		maxHeapify(arr,idx,len);
	}
	for(int idx=len-1;idx>=0;--idx){
		int temp = arr[0];
		arr[0] =arr[idx];
		arr[idx]=temp;
		maxHeapify(arr,0,idx-1);
	}
	return 0;
}
int main(){
	int arr[max_len]={213532,346457,7,658,245,865,345654,745,7,36435};
	heap_sort(arr,max_len);
	for(int idx=0;idx<max_len;++idx){
		printf("%d\n",arr[idx]);
	}
	return 0;
}
