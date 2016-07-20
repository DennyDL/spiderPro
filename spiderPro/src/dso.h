#ifndef _DSO_H_
#define _DSO_H_

#include<map>
#include<string>
#include<stdio.h>

using namespace std;

#define MODULE_OK 	0
#define MODULE_ERR 	1

#define MODULE_MAGOR_VERSION 	1
#define MODULE_SUB_VERSION	0

//typedef void (*INIT)(void *);
//typedef int (*HANDLE)(void *);

struct Module
{
	int version;
	int sub_version;
	char *name;
//	void (*init)(void *);暂时不需要init（）;找到module入口地址就可以了
	int (*handle)(void *);
};

class DsoManager
{
public:
	int load(char* path,char*name);
	Module* getModule(char* name);
	DsoManager();
	~DsoManager();
public:
	static map<string,Module*> modules;
};


#endif

