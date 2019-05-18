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
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
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

int querySql(pSqlData psd)
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





