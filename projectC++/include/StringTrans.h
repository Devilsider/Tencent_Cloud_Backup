#pragma once
#include <string>
#include <codecvt>
#include <locale>

using std::string;
using std::wstring;

namespace  wd
{
class StringTrans
{
public:
    wstring strToWstr(const string &);//将str转换成为wstring
    string WstrToStr(const wstring &);//将wstring转换成为string
};

}
