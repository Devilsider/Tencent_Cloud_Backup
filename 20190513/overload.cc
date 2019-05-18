#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#ifdef __cplusplus
extern "C"
{
#endif
    int add(int x,int y){
        return x+y;
    }
#ifdef __cplusplus
}
#endif

double add(double x,double y){
    return x+y;
}

double add(int x,double y){
    return x+y;
}

double add(double x,int y){
    return x+y;
}

int add(int  x,int y,int z){
    return x+y+z;
}
int main(){
    int a=3,b=4,c=5;
    double d1=1.11,d2=2.22;
    printf("a+b=%d\n",add(a,b));
    cout<<"add(a,b,c)="<<add(a,b,c)<<endl;
    cout<<"add(d1,d2)="<<add(d1,d2)<<endl;
    cout<<"add(d1,a)="<<add(d1,a)<<endl;
    cout<<"add(a,d1)="<<add(a,d1)<<endl;
    return 0;
}
