#include "python2.7/Python.h"
#include <iostream>
using namespace std;

int main()
{
    Py_Initialize() ;
    
    //切换工作路径
    /* string path = "~/projectC++2/test"; */
    /* string chdir_cmd = string("sys.path.append(\"")+path+"\")"; */
    /* const char* cstr_cmd = chdir_cmd.c_str(); */
    /* PyRun_SimpleString("import sys"); */
    /* PyRun_SimpleString(cstr_cmd); */
    /* cout<<cstr_cmd<<endl; */
    /* //加载模块 */
    /* PyObject* moduleName = PyString_FromString("ss");//模块名 */
    /* PyObject* pModule = PyImport_Import(moduleName); */

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject* pModule = PyImport_ImportModule("ss");
    if(!pModule)
    {
        PyErr_Print();
        return 0;
    }
    cout<<"[INFO]Python get module succeed."<<endl;

    //加载函数
    PyObject * pv = PyObject_GetAttrString(pModule,"parse_string");
    if(!pv){
        //验证加载成功
        cout<<"[ERROR]Can't find the function(parse_string)."<<endl;
        return 0;
    }
    cout<<"[INFO]Get function(parse_string) succeed."<<endl;

    string text = "自然语言处理: 是人工智能和语言学领域的分支学科。在这此领域中探讨如何处理及运用自然语言；自然语言认知则是指让电脑“懂”人类的语言。自然语言生成系统把计算机数据转化为自然语言。自然语言理解系统把自然语言转化为计算机程序更易于处理的形式。";

    PyObject * args =PyTuple_New(1);
    PyObject* arg1=PyString_FromString(text.c_str());
    PyTuple_SetItem(args,0,arg1);
    
    //调用函数
    PyObject* pRet = PyObject_CallObject(pv,args);
    //获取参数 
    if(pRet)
    {
        string res = PyString_AsString(pRet);
        cout<<"res = "<<res<<endl;
    }

    Py_Finalize();
    return 0;
}

