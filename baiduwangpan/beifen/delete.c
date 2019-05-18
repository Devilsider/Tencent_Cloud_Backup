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
