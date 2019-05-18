#include <stdio.h>
#include <stdlib.h>
#define len 10
int quick_sort(int arr[],int start,int end){
	if(start>=end){
		return 0;
	}
	int left=start;
	int right=end;
	int pivot=arr[left];
	while(left<right){
		while(arr[right]>=pivot&&left<right){
			--right;
		}
		while(arr[left]<=pivot&&left<right){
			++left;
		}
		if(right>left){
			int temp=arr[left];
			arr[left]=arr[right];
			arr[right]=temp;
		}
	}
	arr[start]=arr[left];
	arr[left]=pivot;
	quick_sort(arr,start,left-1);
	quick_sort(arr,left+1,end);
	return 0;
}
int main(){
	int arr[len]={12337,3246436,123213,41,5432,5,436,5476,8,69879};
	quick_sort(arr,0,len-1);
	for(int idx=0;idx<10;++idx){
		printf("%d\n",arr[idx]);
	}
	return 0;
}


