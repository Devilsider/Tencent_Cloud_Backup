#include<stdio.h>
#include<stdlib.h>
#define max_len 10
int merge_sort(int arr[],int res[],int start,int end){
	if(start>=end){
		return 0;
	}
	int mid=((end-start)>>1)+start;
	int start1=start;
	int end1=mid;
	int start2=mid+1;
	int end2=end;
	merge_sort(arr,res,start1,end1);
   	merge_sort(arr,res,start2,end2);
	int k=start;
	while(start1<=end1&&start2<=end2){
		res[k++]=(arr[start1]<arr[start2])?arr[start1++]:arr[start2++];
	}	
	while(start1<=end1){
		res[k++]=arr[start1++];
	}
	while(start2<=end2)
	{	
		res[k++]=arr[start2++];
	}
	for(k=start;k<=end;++k){
		arr[k]=res[k];
	}
	return 0;
}
int main(){
	int arr[max_len]={1,123,12142341,4123,12354,6,457,6587,69,255};
	int res[max_len];
	merge_sort(arr,res,0,max_len-1);
	for(int idx=0;idx<10;++idx){
		printf("%d\n",arr[idx]);
	}
}

