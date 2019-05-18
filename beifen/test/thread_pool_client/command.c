#include "function.h"

void commandRead(char command[],char comm[],char path[])
{   
//    printf("5I am commandRead,now command is %s\n",command);
    char buf1[10];//命令
    char buf2[1000];//路径
    int i=0; 
    int j=0;
    int k=0;
    //printf("11strlen is %d\n",(int)strlen(command));
    for(i=0;i<(int)strlen(command);++i){
        //读命令 
        bzero(buf1,sizeof(buf1));
        while(command[i]==' '&&i<(int)strlen(command)){
            ++i;
        }
        j=i;
        while(command[i]!=' '&&command[i]!='\n'&&i<(int)strlen(command)){
            ++i;
        }
        for(k=0;k<i-j;++k){
            buf1[k]=command[k+j];
        }
        buf1[++k]='\0';
        j=i;
        //printf("26I am commandCheck,command is %s,command len is %d\n",buf1,(int)strlen(buf1));
        //printf("27command strlen is %d,i=%d\n",(int)strlen(command),i);
        //读取路径,有就读
        bzero(buf2,sizeof(buf2));
        while(command[i]==' '&&i<(int)strlen(command)){
            ++i;
        }
        j=i;
        while(command[i]!=' '&&command[i]!='\n'&&i<(int)strlen(command)){
            ++i;
        }
        for(k=0;k<i-j;++k){
            buf2[k]=command[k+j];
        }
        buf2[++k]='\0';
       // printf("40I am commandRead,path is %s,pathlen is%d\n",buf2,(int)strlen(path));

    }
    strcpy(comm,buf1);
    strcpy(path,buf2);
}
int commandCheck(char comm[],char path[]){
    if(0==strcmp(comm,"cd")){
        //printf("now is cd\n");
        return 1;
    }
    else if(0==strcmp(comm,"ls")){
        return 2;
    }
    else if(0==strcmp(comm,"gets")){
        return 4;
    }
    else if(0==strcmp(comm,"puts")){
        return 3;
    }
    else if(0==strcmp(comm,"pwd")){
        return 6;
    }
    else if(0==strcmp(comm,"remove")){
        return 5;
    }
    else {
        return -1;
    }
    return -1;
}

