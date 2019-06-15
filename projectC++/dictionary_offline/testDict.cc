#include "DictProducer.h"
#include "SplitTool.h"
#include <iostream>

int main()
{
    string test("/home/ubuntu/projectC++/dictionary_offline/test");
    wd::DictProducer dic(test);
    dic.build_dict();
    /* dic.show_files(); */
    dic.show_dict();

    return 0;
}

