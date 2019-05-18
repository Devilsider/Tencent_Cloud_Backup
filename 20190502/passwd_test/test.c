#include <func.h>
struct spwd{
    char *sp_namp;      /* Login name */
    char *sp_pwdp;      /* Encrypted password */
    long    sp_lstchg;  /*Date of last change (measuredin days since 1970-01-01 00:00:00 +0000 (UTC)) */
    long    sp_min;     /* Min # of days between changes */
    long    sp_max;     /* Max # of days between changes */
    long    sp_warn;    /* # of days before password expiresto warn user to change it */
    long    sp_inact;   /* # of days after password expiresuntil account is disabled */
    long    sp_expire;  /* Date when account expires (measuredin days since 1970-01-01 00:00:00 +0000 (UTC)) */
    unsigned long sp_flag;    /* Reserved */
};

void help(void){
    printf("用户密码验证：\n第一个参数为用户名!\n");
    exit(-1);
}

void error_quit(char *msg){
    perror(msg);
    exit(-2);
}
void get_salt(char *salt,char *passwd){
    int i,j;
    //取出salt值，记录密码字符下标j，记录$出现次数
    for(i=0,j=0;passwd[i]&&j!=3;++i){
        if(passwd[i]=='$'){
            ++j;
        }
    }
    strncpy(salt,passwd,i-1);
}
int main(int argc,char **argv){
    struct spwd*sp;
    char *passwd;
    char salt[512]={0};
    if(argc!=2)help();
    //输入用户密码
    passwd=getpass("请输入密码：");
    //得到用户名以及密码，命令行参数的第一个参数作为用户名
    if(NULL==(sp=getspnam(argv[1]))){
        error_quit("获取用户名和密码");
    }
    //得到salt，得到的密码作参数
    get_salt(salt,sp->sp_pwdp);
    //进行密码验证
    if(0==strcmp(sp->sp_pwdp,crypt(passwd,salt))){
        printf("验证通过\n");
    }
    else{
        printf("验证失败\n");
    }
    return 0;
}
