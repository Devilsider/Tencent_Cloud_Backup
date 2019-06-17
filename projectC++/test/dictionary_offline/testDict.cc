#include "/home/ubuntu/projectC++/include/IndexProducer.h"
#include "/home/ubuntu/projectC++/include/DictProducer.h"
#include "/home/ubuntu/projectC++/include/SplitTool.h"
#include <iostream>

int main()
{
    string test("/home/ubuntu/projectC++/data");
    wd::DictProducer dic(test);
    dic.build_dict();
    /* dic.show_files(); */
    /* dic.show_dict(); */
    dic.store_dict("/home/ubuntu/projectC++/data/");

    wd::IndexProducer index("/home/ubuntu/projectC++/data/Dictionary");
    index.init();
    index.showDict();
    index.showIndex();
    return 0;
}

