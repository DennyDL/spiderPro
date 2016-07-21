#include "dso.h"
#include "iostream"

using namespace std;
int handle1(void* arg)//不能和其他动态模块重名，否则只会调用一个函数
{
	cout <<"success =================="<< (int)arg <<endl;
	return 1;
}

Module libtestmod1 = {
    MODULE_MAGOR_VERSION,
    MODULE_SUB_VERSION,
    __FILE__,
    handle1
};
//g++ -fPIC -shared testmod1.cpp -o libtestmod1.so 
//g++ main.cpp dso.cpp qstring.cpp -rdynamic -ldl -g  -o main
