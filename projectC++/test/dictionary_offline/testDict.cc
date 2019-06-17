#include "/home/ubuntu/projectC++/include/IndexProducer.h"
#include "/home/ubuntu/projectC++/include/DictProducer.h"
#include "/home/ubuntu/projectC++/include/SplitTool.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    string test("/home/ubuntu/projectC++/data");
    wd::DictProducer dic(test);
    dic.build_dict();
    /* dic.show_files(); */
    /* dic.show_dict(); */
    dic.store_dict("/home/ubuntu/projectC++/data/");

    wd::IndexProducer * pindex=wd::IndexProducer::getInstance("ss");
    pindex->init();
    pindex->showDict();
    pindex->showIndex();

    for(auto i:*pindex->getDict())
    {
        cout<<"word: "<<i.first<<" frequency:  "<<i.second<<endl;
    }
    for(auto i:*pindex->getIndex())
    {
        cout<<" "<<i.first<<endl;
    }
    return 0;
}

