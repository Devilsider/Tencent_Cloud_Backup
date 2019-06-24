#include "/home/ubuntu/projectC++2/include/DirScanner.h"
#include "MyReaderXML.h"
#include "PageLib.h"
#include <iostream>

int main()
{
    wd::DirScanner dirscanner("../../data/");

    dirscanner.traverse("../../data/");

    /* dirscanner.showVecFiles(); */
    wd::PageLib pagelib(dirscanner);

    pagelib.createFormatPageLib();

    return 0;
}

