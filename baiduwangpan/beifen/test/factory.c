#include "function.h"
void cleanup(void *p){
    pQue_t pq=(pQue_t)p;
    pthread_mutex_unlock(&pq->mutex);
    printf("I am cleanup!\n");
}
/*void *sigFuncALL(void *p){
    //任务分类处理线程
    printf("I am sigFuncALL\n");
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->queAll;
    pNode_t pcur;
    int getSuccess;
    while(1){
        pthread_mutex_lock(&pf->mutex);
        if(1==pf->endFlag){
        pthread_mutex_unlock(&pf->mutex);
            printf("I am sigFuncALL,start exit\n"); 
        }
    }
}*/
void *sigFuncShort(void *p){//短命令处理线程
    printf("I am sigFuncShort\n");
    pFactory_t pf=(pFactory_t)p;
    pQue_t pqS=&pf->queShort;
    pQue_t pqL=&pf->queLong;
    pNode_t pcur;
    int getSuccess;
    //创建动态用户结构体数组
    pUsr pusr,usrBuf;
    pusr=(pUsr)calloc(pqS->queCapacity,sizeof(usr));
    usrBuf=(pUsr)calloc(1,sizeof(usr));
    //记得释放
    //创建epoll句柄
    int epfdS=epoll_create(1);
    if(-1==epfdS) {
        perror("epoll_create");
    }
    struct epoll_event event,*evss;
    evss=(struct epoll_event *)calloc(pqS->queCapacity,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    int ret;
    int readyFdNum;
    Command_t commd;
    Train_t train;
    int usrNum;
    usrNum=0;
    
    //初始化数据库信息
    sqlData sd;
    bzero(&sd,sizeof(sd));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");
    //数据库和命令等用到的时候再初始化
    
    while(1)
    {
EPOLL:
        pthread_mutex_lock(&pf->mutex);
        if(1==pf->endFlag){
        pthread_mutex_unlock(&pf->mutex);
            printf("I am sigFuncShort,start exit\n");
            for(int idx=0;idx<usrNum;++idx) {
                free(&pusr[idx]);
            }
            free(usrBuf);
            exit(0);
        }
        pthread_mutex_unlock(&pf->mutex);
        readyFdNum=epoll_wait(epfdS,evss,pqS->queCapacity,0);
        if(-1==readyFdNum){
            perror("epoll_wait");
        }
        int i,j,k;
        for(i=0;i<readyFdNum;++i)
        {
            if(evss[i].events==EPOLLIN)
            {
                bzero(&commd,sizeof(commd));
              //  printf("commd.len=%d,commd.control_code =%d\n",commd.len,commd.control_code);
    //------------------------------------------------------
                
                ret=recvCycle(evss[i].data.fd,&commd.len,4);
                //printf("------ret---%d\n",ret);
                if(-1==ret){
                   //非正常关闭，找到对应的new_fd，去除监听，并在用户
                   //结构体里面删除
                    for(k=0;k<usrNum;++k){
                        //遍历查找对应的用户 
                        if(evss[i].data.fd==pusr[k].usr_new_fd){
                            bzero(&pusr[k],sizeof(usr));
                            --usrNum;
                            break;
                        }
                    }
                    event.data.fd=evss[i].data.fd;
                    epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                    close(evss[i].data.fd);
                    break;
                }
                ret=recvCycle(evss[i].data.fd,&commd.control_code,commd.len);
                //printf("------ret---%d\n",ret);
                if(-1==ret){
                   //非正常关闭，找到对应的new_fd，去除监听，并在用户
                   //结构体里面删除
                   for(k=0;k<usrNum;++k){
                        //遍历查找对应的用户 
                        if(evss[i].data.fd==pusr[k].usr_new_fd){
                            bzero(&pusr[k],sizeof(usr));
                            --usrNum;
                            break;
                        }
                    }
                    event.data.fd=evss[i].data.fd;
                    epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                    close(evss[i].data.fd);
                    break;
                }
                printf("commd.len=%d,commd.control_code =%d\n",commd.len,commd.control_code);
               // printf("commd.control_code=%d\n",commd.control_code);
                if(3==commd.control_code||4==commd.control_code){
                    //为上传下载命令将其插入上传下载队列
                   /* int l=0;
                    for(l=0;l<usrNum;++l) {
                        if(evss[i].data.fd==pusr[l].usr_new_fd){
                            break;
                        }
                    }
                    bzero(&pcur->node_usr,sizeof(usr));
                    memcpy(&pcur->node_usr,&pusr[l],sizeof(usr));
                    */
                    pNode_t pnew;
                    pnew=(pNode_t)calloc(1,sizeof(Node_t));
                    pnew->node_commd.control_code=commd.control_code; 
                    pnew->new_fd=evss[i].data.fd;
                    pthread_mutex_lock(&pqL->mutex);
                    queInsert(pqL,pnew);
                    pthread_mutex_unlock(&pqL->mutex);
                    event.data.fd=evss[i].data.fd;
                    //从监听队列里面删除，第四期功能这里需修改 
                    /*测试 pNode_t ppp; */
                    /* ppp=pqL->queHead; */
                    /* while(ppp!=NULL){ */
                    /*     printf("--------------------\n"); */
                    /*     printf("short queue new_fd is %d\n",ppp->new_fd); */
                    /*     printf("--------------------\n"); */
                    /*     ppp=ppp->next; */
                    /* } */
                    ret=epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                    if(-1==ret){
                        perror("epoll_ctl");
                    }
                    pthread_cond_signal(&pf->condL);
                }
                else{
                    //printf("-----geiwo jin -----\n");
                    switch(commd.control_code){
                        case 1:
                            {   
                                cdServer(evss[i].data.fd);
                                break;
                            }
                        case 2:{
                                   lsServer(evss[i].data.fd);
                                   break;
                               }
                        case 5:{
                                   removeServer(evss[i].data.fd);
                                   break;
                               }
                        case 6:{
                                   pwdServer(evss[i].data.fd);
                                   break;
                               }
                        //用户登录  
                        //此时将登录信息赋给该用户
                        case 8:
                               {
                               //    printf("---usrNum=%d,---pqS.queCapacity--is%d\n",usrNum,pqS->queCapacity);
                                   ++usrNum;
                                   if(usrNum>pqS->queCapacity){
                                       //用户登录数超过限制
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   bzero(&train,sizeof(Train_t));
                                   ret=recvCycle(evss[i].data.fd,&train.dataLen,4);
                                   if(-1==ret){
                                       //非正常关闭，找到对应的new_fd，去除监听，并在用户
                                       //结构体里面删除
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   ret=recvCycle(evss[i].data.fd,train.buf,train.dataLen);
                                   if(-1==ret){
                                       //非正常关闭，找到对应的new_fd，去除监听，并在用户
                                       //结构体里面删除
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   usr usrTmp;
                                   memcpy(&usrTmp,train.buf,train.dataLen);
                                   //记录操作
                                   
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
                                ,usrTmp.name,8," ");

    //printf("---8--%s\n",sd.sql_command);
                                   insertSql(&sd);

                                   printf("train.datelen=%d,train.buf=%s\n",train.dataLen,train.buf);
                                    //从数据库中查找该salt，再发一次
                                    bzero(sd.sql_command,sizeof(sd.sql_command));
                                    sprintf(sd.sql_command,"%s'%s'","select salt from usr where name ="
                                            ,usrTmp.name);
                                    char sqlBuf[100];
                                    char delim[3]=" \n";
                                    char saltBuf[64];
                                    bzero(saltBuf,sizeof(saltBuf));
                                    bzero(sqlBuf,sizeof(sqlBuf));
                                    querySqlFile(&sd,sqlBuf);
                                    strcpy(saltBuf,strtok(sqlBuf,delim));
                                    printf("------saltBuf---is--%s\n",saltBuf);
                                   bzero(&train,sizeof(Train_t));
                                   train.dataLen=strlen(saltBuf);
                                   memcpy(train.buf,saltBuf,train.dataLen);
                                   printf("-------------train.buf----%s\n",train.buf);
                                   ret=send(evss[i].data.fd,&train,train.dataLen+4,0);
                                   if(-1==ret){
                                       perror("send");
                                   }
                                    //再次接收用户加密数据 
                                   bzero(&train,sizeof(Train_t));
                                   ret=recvCycle(evss[i].data.fd,&train.dataLen,4);
                                   if(-1==ret){
                                       //非正常关闭，找到对应的new_fd，去除监听，并在用户
                                       //结构体里面删除
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   ret=recvCycle(evss[i].data.fd,train.buf,train.dataLen);
                                   if(-1==ret){
                                       //非正常关闭，找到对应的new_fd，去除监听，并在用户
                                       //结构体里面删除
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   for(k=0;k<usrNum;++k){
                                       if(0==pusr[k].usr_new_fd){
                                           //被初始化过得用户
                                           //接收数据赋给
                                           memcpy(&pusr[k],train.buf,train.dataLen);
                                           pusr[k].usr_new_fd=evss[i].data.fd;
                                           ++usrNum;
                                           break;
                                       }
                                   }
                                   printf("usr.name=%s,usr.passwd=%s\n",pusr[k].name,pusr[k].ciphertext);
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s'","select salt,ciphertext from usr where name =",
                                           pusr[k].name);  
                                   ret=querySqlUsr(&sd,usrBuf);
                                    //验证正确则继续，否则删除该客户端监听newFd并断开连接 
                                    
                                              printf("usrBuf.name=%s,usrBuf.salt=%s,usrBuf.passwd=%s\n"
                                                    ,usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                   bzero(&commd,sizeof(Command_t));
                                   commd.len=sizeof(int);
                                   commd.control_code=0;
                                   if(-1==ret){
                                       //数据库查找错误,找到对应的new_fd，去除监听，并在用户
                                       //结构体里面删除
                                        for(k=0;k<usrNum;++k){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[k].usr_new_fd){
                                                bzero(&pusr[k],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        commd.control_code=-1;
                                        ret=send(evss[i].data.fd,&commd.len,4,0); 
                                        ret=send(evss[i].data.fd,&commd.control_code,commd.len,0);
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   if(0!=strcmp(usrBuf->ciphertext,pusr[k].ciphertext)){
                                       //密文验证错误
                                       for(int bbx=0;bbx<usrNum;++bbx){
                                            //遍历查找对应的用户 
                                            if(evss[i].data.fd==pusr[bbx].usr_new_fd){
                                                bzero(&pusr[bbx],sizeof(usr));
                                                --usrNum;
                                                break;
                                            }
                                        }
                                        commd.control_code=-1;
                                        ret=send(evss[i].data.fd,&commd.len,4,0); 
                                        ret=send(evss[i].data.fd,&commd.control_code,commd.len,0);
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   } 
                                   ret=send(evss[i].data.fd,&commd.len,4,0); 
                                   ret=send(evss[i].data.fd,&commd.control_code,commd.len,0);
                                   break;
                               }
                        case 9:{
                        //用户注册
                        //先发送salt过去
                                   bzero(&train,sizeof(Train_t));
                                   char salt[64];
                                   GenerateStr(salt);
                                   train.dataLen=strlen(salt);
                                   memcpy(train.buf,salt,train.dataLen);
                                   printf("-------------train.buf----%s\n",train.buf);
                                   ret=send(evss[i].data.fd,&train,train.dataLen+4,0);
                                   if(-1==ret){
                                       perror("send");
                                   }

                                   bzero(&train,sizeof(Train_t));
                                   ret=recvCycle(evss[i].data.fd,&train.dataLen,4);
                                   printf("ret=%d,train.dataLen=%d\n",ret,train.dataLen);
                                   if(-1==ret){                                               
                                   //非正常关闭，找到对应的new_fd，去除监听，并在用户     
                                   //结构体里面删除                                       
                                       event.data.fd=evss[i].data.fd;                        
                                       epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                       close(evss[i].data.fd);                               
                                       break;
                                   }                                                          
                                   ret=recvCycle(evss[i].data.fd,train.buf,train.dataLen);
                                    printf("ret=%d,train.buf=%s\n",ret,train.buf);
                                   if(-1==ret){                                               
                                   //非正常关闭，找到对应的new_fd，去除监听，并在用户     
                                   //结构体里面删除                                       
                                       event.data.fd=evss[i].data.fd;                        
                                       epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                       close(evss[i].data.fd);                               
                                       break;
                                   }
                                   bzero(usrBuf,sizeof(usr));
                                   memcpy(usrBuf,train.buf,train.dataLen);
                                   
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
                                ,usrBuf->name,9," ");
                                
   // printf("---9--%s\n",sd.sql_command);
                                   insertSql(&sd);
                                   
                                   
                                   strcpy(usrBuf->salt,salt);
                                   //printf("usrBuf.name=%s,usrBuf.salt=%s,usrBuf.passwd=%s\n",usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                   // 写入数据库
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s','%s','%s')","insert into usr (name,salt,ciphertext) values ("
                                           ,usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                   //printf("sd.sql_command=%s\n",sd.sql_command);
                                   int inseSuc=insertSql(&sd);
                                   bzero(&commd,sizeof(Command_t));
                                   commd.len=sizeof(int);
                                   commd.control_code=0; 
                                   if(-1==inseSuc){
                                      //插入失败,通知客户端
                                      commd.control_code=-1;
                                      ret=send(evss[i].data.fd,&commd.len,4,0); 
                                      ret=send(evss[i].data.fd,&commd.control_code,commd.len,0);
                                      event.data.fd=evss[i].data.fd;                        
                                      epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                      close(evss[i].data.fd);                               
                                      break;
                                   }
                                   ret=send(evss[i].data.fd,&commd.len,4,0); 
                                   ret=send(evss[i].data.fd,&commd.control_code,commd.len,0);
                                   //为每个用户分配四个文件夹，src，bin，conf，filedir 
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,
                                           "%s%d,'%s','%s','%s')","insert into virtualDir (precode,fileName,belongID,filetype) values ("
                                   ,0,"src",usrBuf->name,"d");
                                   insertSql(&sd);
                                   sprintf(sd.sql_command,
                                           "%s%d,'%s','%s','%s')","insert into virtualDir (precode,fileName,belongID,filetype) values ("
                                   ,0,"bin",usrBuf->name,"d");
                                   insertSql(&sd);
                                   sprintf(sd.sql_command,
                                           "%s%d,'%s','%s','%s')","insert into virtualDir (precode,fileName,belongID,filetype) values ("
                                   ,0,"conf",usrBuf->name,"d");
                                   insertSql(&sd);
                                   sprintf(sd.sql_command,
                                           "%s%d,'%s','%s','%s')","insert into virtualDir (precode,fileName,belongID,filetype) values ("
                                   ,0,"filedir",usrBuf->name,"d");
                                   insertSql(&sd);
                                   //注册完成后关闭连接要求其重新验证登录,客户端实现 
                                   event.data.fd=evss[i].data.fd;                        
                                   epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                   close(evss[i].data.fd);                               
                                   break;
                               }
                        default:{
                               printf("case 7\n");
                               for(k=0;k<usrNum;++k){
                                //遍历查找对应的用户 
                                if(evss[i].data.fd==pusr[k].usr_new_fd){
                                    bzero(&pusr[k],sizeof(usr));
                                    --usrNum;
                                    break;
                                }
                               }
                               event.data.fd=evss[i].data.fd;
                               epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                               close(evss[i].data.fd);
                               break; 
                        }
                    }
                }
            }
        }
        //将队列节点取下来，用epoll监听 
        pthread_mutex_lock(&pqS->mutex);
        if(!pqS->queSize){
            pthread_mutex_unlock(&pqS->mutex);
            goto EPOLL; 
        }
        getSuccess=queGet(pqS,&pcur);
        pthread_mutex_unlock(&pqS->mutex);
        //监听 
        if(!getSuccess){
            printf("I am sigFuncShort,start epoll\n");
            event.data.fd=pcur->new_fd;
            printf("start epoll pcur.new_fd:%d\n",pcur->new_fd) ;
            ret=epoll_ctl(epfdS,EPOLL_CTL_ADD,pcur->new_fd,&event);
            //加入监听后应该释放该节点
            free(pcur);
            if(-1==ret){
                perror("epoll_ctl");
            }
        }




    }
}

void *sigFuncLong(void *p)//上传下载线程
{
    //判断队列是否为空，为空就睡觉 
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->queLong;
    //pthread_cleanup_push(cleanup,&pf->que);
    pNode_t pcur;
    int getSuccess;
    while(1){
        pthread_mutex_lock(&pf->mutex);
        if(1==pf->endFlag){
        pthread_mutex_unlock(&pf->mutex);
            printf("I am thread,start exit:)\n");
            exit(0);
        }
        pthread_mutex_unlock(&pf->mutex);
        pthread_mutex_lock(&pq->mutex);
        if(!pq->queSize){
            pthread_cond_wait(&pf->condL,&pq->mutex);
        }
        getSuccess=queGet(pq,&pcur);
        pthread_mutex_unlock(&pq->mutex);   
        if(!getSuccess){
            printf("I am thread,strat transfering:)\n");
            if(4==pcur->node_commd.control_code){ 
                //getsfile传参未完成tranFile(pcur->new_fd,NULL);
                tranFile(pcur->new_fd);
            }
            else if(3==pcur->node_commd.control_code){
                //putsfile 未完成
                printf("pcur.new_fd=%d\n",pcur->new_fd);
                clientTranFile(pcur->new_fd);
            } 
            //下载上传完成就关闭,四期改为子线程
            printf("transfer success!\n") ;
            close(pcur->new_fd);
            free(pcur);
        }
    }
    //pthread_cleanup_pop(1);
}

void factoryInit(pFactory_t pf,int threadNum,int capacity){
    bzero(pf,sizeof(Factory_t));
    pf->pthid=(pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->threadNum=threadNum;
    //pthread_cond_init(&pf->condA,NULL);
    pthread_cond_init(&pf->condL,NULL);
    pthread_cond_init(&pf->condS,NULL);
    pthread_mutex_init(&pf->mutex,NULL);
   // queInit(&pf->queAll,capacity);
    queInit(&pf->queLong,capacity);
    queInit(&pf->queShort,capacity);
}
void factoryStart(pFactory_t pf){
    int i;
    if(0==pf->startFlag){
       // pthread_create(pf->pthid,NULL,sigFuncALL,pf);
        pthread_create(pf->pthid,NULL,sigFuncShort,pf);
        for(i=1;i<pf->threadNum;++i){ 
            pthread_create(pf->pthid+i,NULL,sigFuncLong,pf);
        }
        pf->startFlag=1;
    }
}
