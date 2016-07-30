#include "dso.h"
#include "iostream"

using namespace std;
int handleSavehtml(void* arg)
{
	cout <<"success !!!!!!!!!!!!"<< (int)arg <<endl;
	return 1;
}

Module savehtml = {
    MODULE_MAGOR_VERSION,
    MODULE_SUB_VERSION,
    __FILE__,
    handle
};
//g++ main.cpp dso.cpp qstring.cpp -rdynamic -ldl -g  -o main
