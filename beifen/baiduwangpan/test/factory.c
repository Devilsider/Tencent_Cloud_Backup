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
    MYSQL_RES *res;
    res=(MYSQL_RES *)calloc(1,sizeof(MYSQL_RES));
    MYSQL_ROW row;
    row=(MYSQL_ROW)calloc(1,sizeof(MYSQL_ROW));
    //数据库和命令等用到的时候再初始化
    
    while(1){
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
        for(i=0;i<readyFdNum;++i){
            if(evss->events==EPOLLIN){
                bzero(&commd,sizeof(commd));
                printf("commd.len=%d,commd.control_code =%d\n",commd.len,commd.control_code);
                ret=recvCycle(evss[i].data.fd,&commd.len,4);
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
                }
                ret=recvCycle(evss[i].data.fd,&commd,commd.len);
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
                }
                printf("commd.len=%d,commd.control_code =%d\n",commd.len,commd.control_code);
                printf("commd.control_code=%d\n",commd.control_code);
                if(3==commd.control_code||4==commd.control_code){
                    //为上传下载命令将其插入上传下载队列,还不能把命令传进去，暂时未完成
                    pthread_mutex_lock(&pqL->mutex);
                    queInsert(pqL,pcur);
                    pthread_mutex_unlock(&pqL->mutex);
                    event.data.fd=evss[i].data.fd;
                    //从监听队列里面删除，第四期功能这里需修改 
                    ret=epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                    if(-1==ret){
                        perror("epoll_ctl");
                    }
                    pthread_cond_signal(&pf->condL);
                }
                else{
                    switch(commd.control_code){
                        case 1:printf("case 1\n");break;
                        case 2:printf("case 2\n");break;
                        case 5:printf("case 5\n");break;
                        case 6:printf("case 6\n");break;
                        //用户登录  
                        //此时将登录信息赋给该用户
                        case 8:
                               {
                                   ++usrNum;
                                   if(usrNum>pqS->queCapacity){
                                       //用户登录数超过限制
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
                                   }
                                   ret=recvCycle(evss[i].data.fd,&train,train.dataLen);
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
                                   }
                                   printf("train.datelen=%d,train.buf=%s\n",train.dataLen,train.buf);
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
                                   //和数据库数据校验，待实现
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s'","select salt,ciphertext from usr where name =",
                                           pusr[k].name);  
                                   ret=querySqlUsr(&sd,usrBuf);
                                    //验证正确则继续，否则删除该客户端监听newFd并断开连接 
                                    
                                              printf("usrBuf.name=%s,usrBuf.salt=%s,usrBuf.passwd=%s\n"
                                                    ,usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                   bzero(&commd,sizeof(Command_t));
                                   commd.len=sizeof(Command_t);
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
                                        ret=send(evss[i].data.fd,&commd,commd.len,0);
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   }
                                   //验证密码
                                   /*if(res){
                                    printf("1111\n");
                                       while((row=mysql_fetch_row(res))!=NULL){
                                          printf("222\n");
                                           for(unsigned int jdx=0;jdx<mysql_num_fields(res);++jdx){
                                              printf("%8s ",row[jdx]);
                                              bzero(usrBuf,sizeof(usr));
                                              memcpy(usrBuf,row[jdx],strlen(row[jdx]));
                                              printf("usrBuf.name=%s,usrBuf.salt=%s,usrBuf.passwd=%s\n"
                                                     ,usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                           }
                                           printf("\n");
                                       }
                                   }
                                   */
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
                                        ret=send(evss[i].data.fd,&commd,commd.len,0);
                                        event.data.fd=evss[i].data.fd;
                                        epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                        close(evss[i].data.fd);
                                        break;
                                   } 
                                   ret=send(evss[i].data.fd,&commd.len,4,0); 
                                   ret=send(evss[i].data.fd,&commd,commd.len,0);
                                   break;
                               }
                        case 9:{
                        //用户注册
                                   bzero(&train,sizeof(Train_t));
                                   ret=recvCycle(evss[i].data.fd,&train.dataLen,4);
                                   printf("ret=%d,train.dataLen=%d\n",ret,train.dataLen);
                                   if(-1==ret){                                               
                                   //非正常关闭，找到对应的new_fd，去除监听，并在用户     
                                   //结构体里面删除                                       
                                       event.data.fd=evss[i].data.fd;                        
                                       epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                       close(evss[i].data.fd);                               
                                   }                                                          
                                   ret=recvCycle(evss[i].data.fd,&train,train.dataLen);
                                    printf("ret=%d,train.buf=%s\n",ret,train.buf);
                                   if(-1==ret){                                               
                                   //非正常关闭，找到对应的new_fd，去除监听，并在用户     
                                   //结构体里面删除                                       
                                       event.data.fd=evss[i].data.fd;                        
                                       epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                       close(evss[i].data.fd);                               
                                   }
                                   bzero(usrBuf,sizeof(usr));
                                   memcpy(usrBuf,train.buf,train.dataLen);
                                   //printf("usrBuf.name=%s,usrBuf.salt=%s,usrBuf.passwd=%s\n",usrBuf->name,usrBuf->salt,usrBuf->ciphertext);
                                   // 写入数据库
                                   bzero(sd.sql_command,sizeof(sd.sql_command));
                                   sprintf(sd.sql_command,"%s'%s','%s')","insert into usr (name,ciphertext) values ("
                                           ,usrBuf->name,usrBuf->ciphertext);
                                   //printf("sd.sql_command=%s\n",sd.sql_command);
                                   int inseSuc=insertSql(&sd);
                                   bzero(&commd,sizeof(Command_t));
                                   commd.len=sizeof(Command_t);
                                   commd.control_code=0; 
                                   if(-1==inseSuc){
                                      //插入失败,通知客户端
                                      commd.control_code=-1;
                                      ret=send(evss[i].data.fd,&commd.len,4,0); 
                                      ret=send(evss[i].data.fd,&commd,commd.len,0);
                                      event.data.fd=evss[i].data.fd;                        
                                      epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                      close(evss[i].data.fd);                               
                                      break;
                                   }
                                   ret=send(evss[i].data.fd,&commd.len,4,0); 
                                   ret=send(evss[i].data.fd,&commd,commd.len,0);
                                   //注册完成后关闭连接要求其重新验证登录,客户端实现 
                                   event.data.fd=evss[i].data.fd;                        
                                   epoll_ctl(epfdS,EPOLL_CTL_DEL,evss[i].data.fd,&event);
                                   close(evss[i].data.fd);                               
                                   break;
                               }
                        default:
                               printf("case 7\n");break; 
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
            ret=epoll_ctl(epfdS,EPOLL_CTL_ADD,pcur->new_fd,&event);
            if(-1==ret){
                perror("epoll_ctl");
            }
        }
        /*readyFdNum=epoll_wait(epfdS,evss,pqS->queCapacity,0);
        if(-1==readyFdNum){
            perror("epoll_wait");
        }
        int i;
        for(i=0;i<readyFdNum;++i){
            if(evss->events==EPOLLIN){
                bzero(&commd,sizeof(commd));
                recvCycle(evss[i].data.fd,&commd.len,4);
                recvCycle(evss[i].data.fd,&commd,commd.len);
                printf("commd.len=%d,commd.control_code =%d",commd.len,commd.control_code);
                if(3==commd.control_code||4==commd.control_code){
                    //为上传下载命令将其插入上传下载队列,还不能把命令传进去，暂时未完成
                    pthread_mutex_lock(&pqL->mutex);
                    queInsert(pqL,pcur);
                    pthread_mutex_unlock(&pqL->mutex);
                    pthread_cond_signal(&pf->condL);
                }
                else{
                    switch(commd.control_code){
                        case 1:printf("1\n");break;
                        case 2:printf("2\n");break;
                        case 3:printf("3\n");break;
                        case 4:printf("4\n");break;
                        case 5:printf("5\n");break;
                        case 6:printf("6\n");break;
                        default:printf("7\n");break; 
                    }
                }
            }
        }*/
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
            tranFile(pcur->new_fd);
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
