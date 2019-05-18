#include<stdio.h>
#include <stdlib.h>
void test(){
	printf("hello world!");
	printf("dabiaoge!");
	printf("tiaoshi!");
}
void main(){
	int i=1;
	int count=0;
	while(i){
			test();
			++count;
			if(count==100){
				i=0;}

	}
	
}

