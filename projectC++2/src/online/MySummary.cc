#include "MySummary.h"
#include "python2.7/Python.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

string  MySummary::summary(const string &text)
{
    //初始化工作路径
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject* pModule = PyImport_ImportModule("PySummary");
    if(!pModule)
    {
        PyErr_Print();
        return "";
    }
    cout<<"11"<<endl;
    //加载函数
    PyObject * pv = PyObject_GetAttrString(pModule,"parse_string");
    if(!pv)
    {
        //加载失败
        return "";
    }
    PyObject* args = PyTuple_New(1);
    PyObject* arg1 = PyString_FromString(text.c_str());
    PyTuple_SetItem(args,0,arg1);

    //调用函数
    PyObject* pRet = PyObject_CallObject(pv,args);

    //获取返回值
    string res;
    if(pRet)
    {
        res = PyString_AsString(pRet);
    }
    

    Py_Finalize();
    return res;
}

}//end of wd

