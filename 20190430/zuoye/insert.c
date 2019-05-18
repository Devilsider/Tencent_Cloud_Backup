#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="wow18771731658";
	char* database="test";
	/*char query[200]="insert into teacher(teacId,name,subjectId,subjectName) values(";
    sprintf(query,"%s%s,'%s',%s,'%s'%s",query,argv[1],argv[2],argv[3],argv[4],")");*/
    /*char query[200]="insert into student(stuId,name,gender) values(";
    sprintf(query,"%s%s,'%s','%s')",query,argv[1],argv[2],argv[3]);*/
    char query[200]="insert into class(stuId,subjectId) values(";
    sprintf(query,"%s%s,%s)",query,argv[1],argv[2]);
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
		printf("insert success\n");
	}
	mysql_close(conn);
	return 0;
}
