#include "function.h"

int deleteSql(pSqlData psd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
    char server[64];                   
    char user[64];                     
    char password[32];                 
    char database[20];                 
    char query[300];                   
    strcpy(server,psd->sql_server);    
    strcpy(user,psd->sql_usr);         
    strcpy(password,psd->sql_password);
    strcpy(database,psd->sql_database);
    strcpy(query,psd->sql_command);        
    
    int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
		printf("delete success,delete row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}

int insertSql(pSqlData psd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[64];
	char user[64];
	char password[32];
	char database[20];
    char query[300];
    strcpy(server,psd->sql_server);
    strcpy(user,psd->sql_usr);
    strcpy(password,psd->sql_password);
    strcpy(database,psd->sql_database);
    strcpy(query,psd->sql_command);
    
    int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
		printf("insert success\n");
	}
	mysql_close(conn);
	return 0;
}

int querySqlUsr(pSqlData psd,pUsr pusr)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[64];
	char user[64];
	char password[32];
	char database[20];//要访问的数据库名称
	char query[300];
    //初始化
    strcpy(database,psd->sql_database);
    strcpy(server,psd->sql_server);
    strcpy(user,psd->sql_usr);
    strcpy(password,psd->sql_password);
    strcpy(query,psd->sql_command);

	puts(query);
    bzero(pusr,sizeof(usr));
	unsigned int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);
        if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//列数
				for(t=0;t<mysql_num_fields(res);t++)
				{
						printf("%8s ",row[t]);
				}
				printf("\n");
                memcpy(pusr->salt,row[0],strlen(row[0]));
                memcpy(pusr->ciphertext,row[1],strlen(row[1]));
			}
		}else{
			printf("Don't find data\n");
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}


int updateSql(pSqlData psd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[64];
	char user[64];
	char password[32];
	char database[20];
	char query[30];
    strcpy(server,psd->sql_server);    
    strcpy(user,psd->sql_usr);         
    strcpy(password,psd->sql_password);
    strcpy(database,psd->sql_database);
    strcpy(query,psd->sql_command);    

    int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("update success\n");
	}
	mysql_close(conn);
	return 0;
}




int querySqlFileMd5(pSqlData psd,pVirtualDir_t pvd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[64];
	char user[64];
	char password[32];
	char database[20];//要访问的数据库名称
	char query[300];
    //初始化
    strcpy(database,psd->sql_database);
    strcpy(server,psd->sql_server);
    strcpy(user,psd->sql_usr);
    strcpy(password,psd->sql_password);
    strcpy(query,psd->sql_command);

	puts(query);
	unsigned int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);
        if(res)
		{   
            if(NULL==mysql_fetch_row(res)){
                return -1;
            }
            while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//列数
				for(t=0;t<mysql_num_fields(res);t++)
				{
						printf("%8s ",row[t]);
                        memcpy(&pvd->vir_filesize,row[t],sizeof(pvd->vir_filesize));
				}
				printf("\n");
			}
		}else{
			printf("Don't find data\n");
            return -1;
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

int querySqlFile(pSqlData psd,char buf[])
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char server[64];
	char user[64];
	char password[32];
	char database[20];//要访问的数据库名称
	char query[300];
    //初始化
    strcpy(database,psd->sql_database);
    strcpy(server,psd->sql_server);
    strcpy(user,psd->sql_usr);
    strcpy(password,psd->sql_password);
    strcpy(query,psd->sql_command);

	puts(query);
	unsigned int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
	//	printf("Query made...\n");
		res=mysql_use_result(conn);
        if(res)
		{   
            if(NULL==(row=mysql_fetch_row(res))){
                return -1;
            }
            r=0;
            for(t=0;t<mysql_num_fields(res);t++)
			{
					printf("%8s ",row[t]);
		            strcpy(buf+r,row[t]);
                    r=r+strlen(row[t]);
                    buf[r]=' ';
                    ++r;
            }
            buf[r]='\n';
            /* printf("int sql buf is %s\n",buf); */
			printf("\n");
            while((row=mysql_fetch_row(res))!=NULL)
			{	
				/* printf("num=%d\n",mysql_num_fields(res));//列数 */
				for(t=0;t<mysql_num_fields(res);t++)
				{
						printf("%8s ",row[t]);
			            strcpy(buf+r,row[t]);
                        r=r+strlen(row[t]);
                        buf[r]=' ';
                        ++r;
                }
                buf[r]='\n';
				printf("\n");
			}
		}else{
			printf("Don't find data\n");
            return -1;
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
