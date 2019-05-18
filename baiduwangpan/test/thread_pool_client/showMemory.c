#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void showMemory(void* begin,int len)
{
	int i;
	char tmp;
	char *start=(char*)begin;
	for(i=0;i<len;i++)
	{
		if((tmp=start[i]>>4&0x0f)<=9)
		{
			putchar(tmp+'0');
		}else{
			putchar(tmp-10+'A');
		}
		if((tmp=start[i]&0x0f)<=9)
		{
			putchar(tmp+'0');
		}else{
			putchar(tmp-10+'A');
		}
		putchar(' ');
		if(i&&i%8==0)
		{
			printf("\n");
		}
	}
}

