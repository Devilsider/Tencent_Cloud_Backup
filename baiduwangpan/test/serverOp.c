#include "function.h"

int pwdServer(int socketFd)
{
    //接收客户端发的用户当前目录消息 
    int ret;
    Train_t train;
    usr usrBuf;
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");

    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&usrBuf,train.buf,train.dataLen);
    //printf("usr.name is %s,usr.salt is %s,usr.ciphertext is %s,usr.precode is %d\n",usrBuf.name,usrBuf.salt,usrBuf.ciphertext,usrBuf.precode);
    //写入日志
    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,usrBuf.name,6," ");
    
//    printf("---6--%s\n",sd.sql_command);
    insertSql(&sd);



    char pathBuf[100];
    int route[100];
    int precodeBuf=usrBuf.precode;
    //precodeBuf=41;
///可封装为路径查找函数
    int i=0;
    route[i]=precodeBuf;
    ++i;
    bzero(sd.sql_command,sizeof(sd.sql_command));
    while(precodeBuf!=0){
        sprintf(sd.sql_command,"%s%d%s'%s'","select precode from virtualDir where code="
                ,precodeBuf," and fileType='d' and belongID=",usrBuf.name);
        ret=querySqlFile(&sd,pathBuf);
        char delim[3]=" \n";
        route[i]=atoi(strtok(pathBuf,delim));
        precodeBuf=route[i];
        ++i;
    }
    /* for(int idx=0;idx<i;++idx){ */
    /*     printf("--%d\n",route[idx]); */
    /* } */
    //逆置route数组
    for(int idx=0;idx<i/2;++idx){
        int temp;
        temp=route[idx];
        route[idx]=route[i-idx-1];
        route[i-idx-1]=temp;
    }
//封装到这
    /* printf("xasdasdasd\n"); */
    /* printf("i=%d\n",i); */
    /* for(int idx=0;idx<i;++idx){ */
    /*     printf("--%d\n",route[idx]); */
    /* } */
    //顺序从数据库中查找来拼接路径
    //可封装为路径拼接函数
    char tempPath[100];
    char usrPath[100];
    char temppp[100];
    char delim[3]=" \n";
    bzero(sd.sql_command,sizeof(sd.sql_command));
    bzero(usrPath,sizeof(usrPath));
    for(int idx=1;idx<i;++idx)
    {
        sprintf(sd.sql_command,"%s%d%s'%s'","select fileName from virtualDir where code="
                ,route[idx]," and fileType='d' and belongID=",usrBuf.name);
        ret=querySqlFile(&sd,pathBuf);
        bzero(temppp,sizeof(temppp));
        strcpy(temppp,strtok(pathBuf,delim));
        //printf("---%s\n",temppp );
        bzero(tempPath,sizeof(tempPath));
        sprintf(tempPath,"%s/%s",usrPath,temppp);
        strcpy(usrPath,tempPath);
    //    printf("usrPath is %s\n",usrPath);
    }
    //printf("usrPath is %s\n",usrPath);
    //routeSprintf(sd,usrBuf,route,i,usrPath);
    //printf("--------%s\n",usrPath);
    //路径拼接完成 ，发过去
    bzero(&train,sizeof(train));
    train.dataLen=strlen(usrPath);
    memcpy(train.buf,usrPath,train.dataLen);
    ret=send(socketFd,&train.dataLen,4,0);
    ERROR_CHECK(ret,-1,"send");
    ret=send(socketFd,train.buf,train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    printf("usrPath is %s,ret=%d\n",train.buf,ret);
    return 0;
}

int cdServer(int socketFd){
    int ret;
    Train_t train;
    usr usrBuf;
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");
    //接收用户数据
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&usrBuf,train.buf,train.dataLen);
    printf("usr.name is %s,usr.salt is %s,usr.ciphertext is %s,usr.precode is %d\n",usrBuf.name,usrBuf.salt,usrBuf.ciphertext,usrBuf.precode);
    //接收路径
    char path[100];
    bzero(path,sizeof(path));
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&path,train.buf,train.dataLen);
    //printf("path is %s\n",path);

    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,usrBuf.name,1,path);

    printf("---1--%s\n",sd.sql_command);
    insertSql(&sd);
    //只考虑三种情况
    int precodeBuf;
    int route[100];
    char pathBuf[100];
    precodeBuf=usrBuf.precode;
    bzero(route,sizeof(route));
    //precodeBuf=41;
    //cd ..
    if(0==strcmp("..",path)){
        int i=0;
        route[i]=precodeBuf;
        ++i;
        bzero(sd.sql_command,sizeof(sd.sql_command));
        while(precodeBuf!=0){
            sprintf(sd.sql_command,"%s%d%s'%s'","select precode from virtualDir where code="
                    ,precodeBuf," and fileType='d' and belongID=",usrBuf.name);
            ret=querySqlFile(&sd,pathBuf);
            char delim[3]=" \n";
            route[i]=atoi(strtok(pathBuf,delim));
            precodeBuf=route[i];
            ++i;
        }
        /* for(int idx=0;idx<i;++idx){ */
        /*     printf("--%d\n",route[idx]); */
        /* } */
        //逆置route数组
        for(int idx=0;idx<i/2;++idx){
            int temp;
            temp=route[idx];
            route[idx]=route[i-idx-1];
            route[i-idx-1]=temp;
        }
        //usr所处虚拟目录的precode改变
        if(i!=1){
            usrBuf.precode=route[i-2];
        }
        //将precode和path发过去
        //顺序从数据库中查找来拼接路径
        //可封装为路径拼接函数
        char tempPath[100];
        char usrPath[100];
        char temppp[100];
        char delim[3]=" \n";
        bzero(sd.sql_command,sizeof(sd.sql_command));
        bzero(usrPath,sizeof(usrPath));
        for(int idx=1;idx<i-1;++idx)
        {
            sprintf(sd.sql_command,"%s%d%s'%s'","select fileName from virtualDir where code="
                    ,route[idx]," and fileType='d' and belongID=",usrBuf.name);
            ret=querySqlFile(&sd,pathBuf);
            bzero(temppp,sizeof(temppp));
            strcpy(temppp,strtok(pathBuf,delim));
            //printf("---%s\n",temppp );
            bzero(tempPath,sizeof(tempPath));
            sprintf(tempPath,"%s/%s",usrPath,temppp);
            strcpy(usrPath,tempPath);
            printf("usrPath is %s\n",usrPath);
        }
        //路径path和precode发送过去 
        bzero(&train,sizeof(Train_t));
        train.dataLen=strlen(usrPath);
        memcpy(train.buf,usrPath,train.dataLen);
        ret=send(socketFd,&train,train.dataLen+4,0);
        //printf("----------ret=%d\n",ret);
        ERROR_CHECK(ret,-1,"send");
            //printf("usrPath is %s\n",usrPath);
        bzero(&train,sizeof(Train_t));
        train.dataLen=sizeof(int);
        memcpy(train.buf,&usrBuf.precode,train.dataLen);
        ret=send(socketFd,&train,train.dataLen+4,0);
        //printf("----------%d\n",usrBuf.precode)    ;
    }
    else{
        //分割路径，若是只有一个则为 cd 文件夹，有多个就是打开绝对路径
        int count=0;
        char newPath[100];
        char sqlBuf[100];
        strcpy(newPath,path);
        bzero(pathBuf,sizeof(pathBuf));
        bzero(route,sizeof(route));
        bzero(sd.sql_command,sizeof(sd.sql_command));
        char delim[3]="/";
        char *p;
        strcpy(pathBuf,strtok(newPath,delim));
        printf("-------%s\n",pathBuf);
        sprintf(sd.sql_command,"%s'%s'%s'%s'","select code from virtualDir where fileName="
                ,pathBuf," and fileType='d' and belongID=",usrBuf.name);
        ret=querySqlFile(&sd,sqlBuf);
        route[count]=atoi(sqlBuf);
        ++count;
        if(-1==ret){
            //没有该目录
            //不响应发送空过去
            bzero(&train,sizeof(Train_t));
            train.dataLen=0;
            ret=send(socketFd,&train,train.dataLen+4,0);
            //printf("----------ret=%d\n",ret);
            ERROR_CHECK(ret,-1,"send");
            //printf("usrPath is %s\n",usrPath);
            bzero(&train,sizeof(Train_t));
            train.dataLen=sizeof(int);
            memcpy(train.buf,&usrBuf.precode,train.dataLen);
            ret=send(socketFd,&train,train.dataLen+4,0);
            printf("---------------usr.precode----%d\n",usrBuf.precode);
            ERROR_CHECK(ret,-1,"send");
            return -1;
        }
        while((p=strtok(NULL,delim))){
            strcpy(pathBuf,p);
            printf("-------%s\n",pathBuf);
            sprintf(sd.sql_command,"%s'%s'%s'%s'","select code from virtualDir where fileName="
                ,pathBuf," and fileType='d' and belongID=",usrBuf.name);
            ret=querySqlFile(&sd,sqlBuf);
            if(-1==ret){
                //没有该目录
                //不响应发送空过去
                bzero(&train,sizeof(Train_t));
                train.dataLen=0;
                ret=send(socketFd,&train,train.dataLen+4,0);
                //printf("----------ret=%d\n",ret);
                ERROR_CHECK(ret,-1,"send");
                //printf("usrPath is %s\n",usrPath);
                bzero(&train,sizeof(Train_t));
                train.dataLen=sizeof(int);
                memcpy(train.buf,&usrBuf.precode,train.dataLen);
                ret=send(socketFd,&train,train.dataLen+4,0);
                printf("---------------usr.precode----%d\n",usrBuf.precode);
                ERROR_CHECK(ret,-1,"send");
                return -1;
            }
            route[count]=atoi(sqlBuf);
            ++count;
        }
        /* for(int idx=0;idx<count;++idx){ */
        /*     printf("route---%d\n",route[idx]); */
        /* } */
        //将路径拼接起来
        bzero(newPath,sizeof(newPath));
        routeSprintf(sd,usrBuf,route,count,newPath);
        bzero(&train,sizeof(Train_t));
//        printf("----aaaa---aaa--newpath--%s\n",newPath) ;
        train.dataLen=strlen(newPath);
        memcpy(train.buf,newPath,train.dataLen);
        ret=send(socketFd,&train,train.dataLen+4,0);
        //printf("----------ret=%d\n",ret);
        ERROR_CHECK(ret,-1,"send");
            //printf("usrPath is %s\n",usrPath);
        usrBuf.precode=route[count-1];
        bzero(&train,sizeof(Train_t));
        train.dataLen=sizeof(int);
        memcpy(train.buf,&usrBuf.precode,train.dataLen);
        ret=send(socketFd,&train,train.dataLen+4,0);
    }
    return 0;
}
int lsServer(int socketFd){
    int ret;
    Train_t train;
    usr usrBuf;
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");
    //接收用户数据
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&usrBuf,train.buf,train.dataLen);
    printf("usr.name is %s,usr.salt is %s,usr.ciphertext is %s,usr.precode is %d\n",usrBuf.name,usrBuf.salt,usrBuf.ciphertext,usrBuf.precode);
    //接收路径
    char path[100];
    bzero(path,sizeof(path));
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&path,train.buf,train.dataLen);
    printf("path is %s\n",path);

    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,usrBuf.name,2,path);
    //printf("---2--%s\n",sd.sql_command);
    insertSql(&sd);
    
    int count=0;
    int route[100];
    char newPath[100];
    char sqlBuf[100];
    char pathBuf[100];
    if(0!=strlen(path)){
        strcpy(newPath,path);
        bzero(pathBuf,sizeof(pathBuf));
        bzero(route,sizeof(route));
        bzero(sd.sql_command,sizeof(sd.sql_command));
        char delim[3]="/";
        char *p;
        strcpy(pathBuf,strtok(newPath,delim));
        printf("-------%s\n",pathBuf);
        sprintf(sd.sql_command,"%s'%s'%s'%s'","select code from virtualDir where fileName="
                ,pathBuf," and fileType='d' and belongID=",usrBuf.name);
        ret=querySqlFile(&sd,sqlBuf);
        route[count]=atoi(sqlBuf);
        ++count;
        if(-1==ret){
            //没有该目录
            //不响应发送空过去
            bzero(&train,sizeof(Train_t));
            train.dataLen=0;
            ret=send(socketFd,&train,train.dataLen+4,0);
            //printf("----------ret=%d\n",ret);
            ERROR_CHECK(ret,-1,"send");
            //printf("usrPath is %s\n",usrPath);
            bzero(&train,sizeof(Train_t));
            train.dataLen=sizeof(int);
            memcpy(train.buf,&usrBuf.precode,train.dataLen);
            ret=send(socketFd,&train,train.dataLen+4,0);
            printf("---------------usr.precode----%d\n",usrBuf.precode);
            ERROR_CHECK(ret,-1,"send");
            return -1;
        }
        while((p=strtok(NULL,delim))){
            strcpy(pathBuf,p);
            printf("-------%s\n",pathBuf);
            sprintf(sd.sql_command,"%s'%s'%s'%s'","select code from virtualDir where fileName="
                ,pathBuf," and fileType='d' and belongID=",usrBuf.name);
            ret=querySqlFile(&sd,sqlBuf);
            if(-1==ret){
                //没有该目录
                //不响应发送空过去
                bzero(&train,sizeof(Train_t));
                train.dataLen=0;
                ret=send(socketFd,&train,train.dataLen+4,0);
                //printf("----------ret=%d\n",ret);
                ERROR_CHECK(ret,-1,"send");
                //printf("usrPath is %s\n",usrPath);
                bzero(&train,sizeof(Train_t));
                train.dataLen=sizeof(int);
                memcpy(train.buf,&usrBuf.precode,train.dataLen);
                ret=send(socketFd,&train,train.dataLen+4,0);
                printf("---------------usr.precode----%d\n",usrBuf.precode);
                ERROR_CHECK(ret,-1,"send");
                return -1;
            }
            route[count]=atoi(sqlBuf);
            ++count;
        }
        /* for(int idx=0;idx<count;++idx){ */
        /*     printf("route---%d\n",route[idx]); */
        /* } */
    }
    else{
        route[count]=usrBuf.precode;
        ++count;
    } 
    int lsCode=route[count-1];
    //printf("--------------%d\n",lsCode);
    bzero(sd.sql_command,sizeof(sd.sql_command));
    //先查找文件
    sprintf(sd.sql_command,"%s%d%s'%s'","select fileName,fileType from virtualDir where precode="
            ,lsCode," and belongID=",usrBuf.name);
    bzero(pathBuf,sizeof(pathBuf));
    bzero(sqlBuf,sizeof(sqlBuf));
    bzero(newPath,sizeof(newPath));
    querySqlFile(&sd,sqlBuf);
    /* char delim[3]="\n"; */
    /* char *p; */
    printf("----sqlBuf is %s\n",sqlBuf);
    /* strcpy(pathBuf,strtok(sqlBuf,delim)); */
  /* //  sprintf(sendPath,"%s%s",pathBuf,) */
    /* printf("---------pathBuf is %s\n",pathBuf); */
    /* while((p=strtok(NULL,delim))){ */
    /*     printf("111\n"); */
    /*     bzero(pathBuf,sizeof(pathBuf)); */
    /*     strcpy(pathBuf,p); */
    /*     printf("---------pathBuf is %s\n",pathBuf); */
    /* } */
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(sqlBuf);
    memcpy(train.buf,sqlBuf,train.dataLen);
    ret=send(socketFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");

    return 0;
}
int removeServer(int socketFd){
    int ret;
    Train_t train;
    usr usrBuf;
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");
    //接收用户数据
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&usrBuf,train.buf,train.dataLen);
    printf("usr.name is %s,usr.salt is %s,usr.ciphertext is %s,usr.precode is %d\n",usrBuf.name,usrBuf.salt,usrBuf.ciphertext,usrBuf.precode);
    //接收路径
    
    char path[100];
    bzero(path,sizeof(path));
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(&path,train.buf,train.dataLen);
    printf("path is %s\n",path);
 

    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,usrBuf.name,5,path);
   // printf("---5--%s\n",sd.sql_command);
    insertSql(&sd);
    
    char sqlBuf[256];
    char md5sumBuf[256];
    int fileLink;
    sprintf(sd.sql_command,"%s'%s'%s'%s'%s","select md5sum from virtualDir where fileName="
            ,path," and belongID= ",usrBuf.name," and fileType='f'");
    ret=querySqlFile(&sd,sqlBuf);
    //printf("------strlen(md5sumBuf)--%d\n",(int)strlen(md5sumBuf));
    printf("-----------ret====%d\n",ret);
    if(-1==ret){
        //数据库中没有该文件,什么也不做，返回
        return 0;
    }
    char delim[3]=" \n"; 
    strcpy(md5sumBuf,strtok(sqlBuf,delim));
    /* printf("------%s\n",md5sumBuf); */
    //printf("sd.sql_command=%s\n",sd.sql_command);
    
    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s'","select count(md5sum) from virtualDir where md5sum="
            ,md5sumBuf);
    bzero(sqlBuf,sizeof(sqlBuf));
    querySqlFile(&sd,sqlBuf);
    fileLink=atoi(strtok(sqlBuf,delim));
    printf("fileLink=%d\n",fileLink);
    //数据库中查找该文件并且统计其次数，若是为1则删除，不为1则删除记录
    if(1==fileLink){
        //删除文件和记录
        bzero(sd.sql_command,sizeof(sd.sql_command));
        sprintf(sd.sql_command,"%s'%s'%s'%s'","delete from virtualDir where md5sum=",
                md5sumBuf," and belongID=",usrBuf.name);
        deleteSql(&sd);
        remove(md5sumBuf);
    }
    else if(fileLink>1){
        //删除记录即可
        bzero(sd.sql_command,sizeof(sd.sql_command));
        sprintf(sd.sql_command,"%s'%s'%s'%s'","delete from virtualDir where md5sum=",
                md5sumBuf," and belongID=",usrBuf.name);
        deleteSql(&sd);
    }

    return 0;
}

int routeSearch(sqlData sd,usr usrBuf,int route[]){ char pathBuf[100]; int precodeBuf=usrBuf.precode;
    //precodeBuf=41;
///可封装为路径查找函数
    int i=0;
    int ret;
    route[i]=precodeBuf;
    ++i;
    bzero(sd.sql_command,sizeof(sd.sql_command));
    while(precodeBuf!=0){
        sprintf(sd.sql_command,"%s%d %s'%s'","select precode from virtualDir where code="
                ,precodeBuf," and fileType='d' and belongID=",usrBuf.name);
        ret=querySqlFile(&sd,pathBuf);
        char delim[3]=" \n";
        route[i]=atoi(strtok(pathBuf,delim));
        precodeBuf=route[i];
        ++i;
    }
    /* for(int idx=0;idx<i;++idx){ */
    /*     printf("--%d\n",route[idx]); */
    /* } */
    //逆置route数组
    for(int idx=0;idx<i/2;++idx){
        int temp;
        temp=route[idx];
        route[idx]=route[i-idx-1];
        route[i-idx-1]=temp;
    }
    return 0;
}
int routeSprintf(sqlData sd,usr usrBuf,int route[],int routeLen,char usrPath[]){
        char tempPath[100];
        char pathBuf[100];
        char temppp[100];
        char delim[3]=" \n";
        int ret;
        bzero(sd.sql_command,sizeof(sd.sql_command));
        //bzero(usrPath,sizeof(usrPath));
        for(int idx=0;idx<routeLen;++idx)
        {
            sprintf(sd.sql_command,"%s%d%s'%s'","select fileName from virtualDir where code="
                    ,route[idx]," and fileType='d' and belongID=",usrBuf.name);
            ret=querySqlFile(&sd,pathBuf);
            bzero(temppp,sizeof(temppp));
            strcpy(temppp,strtok(pathBuf,delim));
            //printf("---%s\n",temppp );
            bzero(tempPath,sizeof(tempPath));
            sprintf(tempPath,"%s/%s",usrPath,temppp);
            strcpy(usrPath,tempPath);
        //    printf("usrPath is %s\n",usrPath);
        }
        return 0;
}
