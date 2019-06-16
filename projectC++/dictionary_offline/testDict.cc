#include "IndexProducer.h"
#include "DictProducer.h"
#include "SplitTool.h"
#include <iostream>

int main()
{
    string test("/home/ubuntu/projectC++/dictionary_offline/test");
    wd::DictProducer dic(test);
    dic.build_dict();
    /* dic.show_files(); */
    /* dic.show_dict(); */
    dic.store_dict("/home/ubuntu/projectC++/dictionary_offline/test/");

    wd::IndexProducer index("/home/ubuntu/projectC++/dictionary_offline/test/Dictionary");
    index.init();
    index.showDict();
    index.showIndex();
    return 0;
}

