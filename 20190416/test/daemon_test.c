#include<func.h>
int daemon_test(){
	setsid();
	chdir("/");
	umask(0);
	int i;
	for(i=0;i<3;++i){
		close(i);	
	}
	return 0;
}
int main(){
	if(fork()){
		exit(0);
	}
	daemon_test();
	while(1){
		sleep(1);
	}

return 0;
}
