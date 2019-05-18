#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::vector;

vector<string> file;
void test0(){
    ifstream ifs;
    ifs.open("io2.cc");
    if(!ifs.is_open()){
        cout<<">>ifstream open file error!"<<endl;
        return;
    }
    string line;
    while(std::getline(ifs,line)){
        cout<<line<<endl;
        file.push_back(line);
    }
    ifs.close();
}
void test1(){
    test0();
    ofstream ofs("test.txt",std::ios::app);
    if(!ofs){
        cout<<"ofstream open file error !"<<endl;
        return; 
    }
    cout<<"pos ="<<ofs.tellp()<<endl;
    ofs<<"that's new line!"<<endl;
    ofs.close();
    
}

void test2(){
    ifstream ifs("test.txt",std::ios::ate);
    if(!ifs){
        cout<<">> ifstream open file error "<<endl;
        return ;
    }
    cout<<"pos= "<<ifs.tellg()<<endl;
    ifs.close();

}

void printCinStatus(fstream &fs){
    cout<<"fs's badbit= "<<fs.bad()<<endl
        <<"fs's failbit= "<<fs.fail()<<endl
        <<"fs's eofbit= "<<fs.eof()<<endl
        <<"fs's goodbit= "<<fs.good()<<endl;
}
void test3(){
    fstream fs("test2.txt");
    if(!fs.is_open()){
        cout<<"fstream open file error!"<<endl;
        return ;
    }
    int number;
    cout<<"pls input 10 intengers :"<<endl;
    for(int idx=0;idx!=10;++idx){
        std::cin>>number;
        fs<<number<<" ";
    }
    cout<<endl;
    fs.seekg(0);

    for(int idx=0;idx!=10;++idx){
        fs>>number;
        cout<<number<<" ";
    }
    cout<<endl;

    fs.close();

}

void test4(){
    string filename="vector.cc";
    ifstream ifs(filename,std::ios::ate);
    if(ifs.is_open()){
        cout<<">> ifstream open file "<<filename<<"error!"<<endl;
        return;
    }

    int length=ifs.tellg();
    cout<<">> length "<<length<<endl;
    char *buff=new char[length+1]();

    ifs.seekg(std::ios::beg);
    ifs.read(buff,length);
    string content(buff);
    cout<<"content :------"
        <<content<<endl
        <<"-------"<<endl;
    delete []buff;
    ifs.close();
}

int main()
{
    test0() ;
    test1();
    test2();
    test3();
    test4();
    return 0;
}

