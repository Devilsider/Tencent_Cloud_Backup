#include "function.h"

int usrUi(pUsr_t pusr)
{
    char key; 
    while(1){
        system("clear");
        printf("--------------------------------------------------------------------\n");
        printf("                            1.user login\n");
        printf("                            2.user register\n");
        printf("--------------------------------------------------------------------\n");
        fflush(stdin);
        scanf("%s",&key);
        printf("the key is %d\n",atoi(&key));
        switch(atoi(&key)){
            case 1:
                usrLog(pusr);
                return 8;//control_code 8
                break;
            case 2:
                usrLog(pusr);
                return 9;//control_code 9
                break;
            default:
                break;
        }
    }
    return -1;
}

void  usrLog(pUsr_t pusr) {//用户登录信息输入
	char temp[20];
	int idx = 0;
	printf(">>Please enter your user name:\n");
	printf(">>User Name:");
	scanf("%s",pusr->name);
	printf(">>Please enter your password :\n");
	printf(">>User Password:");
    getchar(); 
    set_disp_mode(STDIN_FILENO,0);
    while (((temp[idx] = getchar()) != '\r') && idx < 20) {
        if(temp[idx]=='\n'){
            break;
        }
        else if (temp[idx] == '\b'&&idx > 0) {
			printf("\b \b");
			--idx;
		}
		else if (temp[0] == '\b') {

		}
		else {
			++idx;
		}
	}
	printf("\n");
	temp[idx] = '\0';
	strcpy(pusr->ciphertext,temp);
    set_disp_mode(STDIN_FILENO,1);
}

//函数set_disp_mode用于控制是否开启输入回显功能  
//如果option为0，则关闭回显，为1则打开回显  
int set_disp_mode(int fd,int option)  
{  
   int err;  
   struct termios term;  
   if(tcgetattr(fd,&term)==-1){  
     perror("Cannot get the attribution of the terminal");  
     return 1;  
   }  
   if(option)  
        term.c_lflag|=ECHOFLAGS;  
   else  
        term.c_lflag &=~ECHOFLAGS;  
   err=tcsetattr(fd,TCSAFLUSH,&term);  
   if(err==-1 && err==EINTR){  
        perror("Cannot set the attribution of the terminal");  
        return 1;  
   }  
   return 0;  
} 
