#ifndef _DSO_H_
#define _DSO_H_

#include<map>
#include<string>
#include<stdio.h>

using namespace std;

#define MODULE_OK 	1
#define MODULE_ERR 	0

#define MODULE_MAGOR_VERSION 	1
#define MODULE_SUB_VERSION	0

struct Module
{
	int version;
	int sub_version;
	char *name;
	int (*handle)(void *);
};

struct HandleData
{
	char *data;
	char *http_header;
	const char *path;
};

class DsoManager
{
public:
	int load(char* path,char* name);
	Module* getModule(char* name);
//	DsoManager();
//	~DsoManager();
public:
	map<string,Module*> m_modules;
};


#endif

