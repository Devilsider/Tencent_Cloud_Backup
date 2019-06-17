#include "/home/ubuntu/projectC++/include/MinEditDistance.h"
#include <iostream>


int main()
{
    wd::MinEditDistance minEdit; 

    string s1("horse");
    string s2("ros");

    int ret= minEdit.editDistance(s1,s2);

    cout<<" "<<ret<<endl;
    return 0;
}

