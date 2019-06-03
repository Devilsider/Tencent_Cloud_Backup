#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <iostream>
using namespace std;

struct FileCloser
{
    void operator()(FILE  *fp)const{
        if(fp){
            fclose(fp);
            cout<<">> fclose(fd)"<<endl;
        }
    }
};

void test0(){
    unique_ptr<FILE,FileCloser> up(fopen("test.txt","a+"));
    string msg("this is a new line\n");
    fwrite(msg.c_str(),1,msg.size(),up.get());
    
}
int main()
{
    test0() ;
    return 0;
}

