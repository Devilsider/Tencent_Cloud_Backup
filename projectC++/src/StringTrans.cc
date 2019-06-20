#include "StringTrans.h"
#include <iostream>
namespace wd
{

wstring StringTrans::strToWstr(const string &str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> convert;
    return convert.from_bytes(str);
}

string StringTrans::WstrToStr(const wstring &wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> convert;
    return convert.to_bytes(wstr);
}

}



