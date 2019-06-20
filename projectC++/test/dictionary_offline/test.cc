#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
    wstring ws1=L"计划完成令计划的计划";
    ofstream ofs("test.txt");
    for(int idx=0;idx<(int)ws1.size();++idx)
    {
        wcout<<ws1.substr(idx,1)<<endl;
        wprintf(L"%s\n",ws1.substr(idx,1).c_str());
    }
    return 0;
}

