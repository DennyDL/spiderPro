#include <iostream>
#include <list>
#include <string>
#include "confparser.h"//在confparser.cpp也包含了confparser.h，所以注意不要重复定义
#define CONF_PATH "spider.conf"
using namespace std;
ConfigParser* ConfigParser::__self = NULL;//放在confparser.h会出现重复定义，注意，static是在编译阶段就分配内存

int main()
{
	list<string>::iterator itor;
	ConfigParser* cp = ConfigParser::instance();
	cp->loader(CONF_PATH);
	cout<<"log_level:"<<cp->getLogLevel()<<endl;
	cout<<"depth:"<<cp->getDepth()<<endl;
	cout<<"job_num:"<<cp->getJobNum()<<endl;
	cout<<"seed:"<<cp->getUrlSeed()<<endl;
	
	cout<<"module_path:"<<cp->getModulePath()<<endl;
	list<string> module_name = cp->getModuleNames();
	itor = module_name.begin();
	while(itor!=module_name.end())
    {
	  cout<< "module_name:"<<*itor<<endl;
	  itor++;
    } 

	list<string> file_type = cp->getFileTypes();
	itor = file_type.begin();
	while(itor!=file_type.end())
    {
	  cout<< "file_type:"<<*itor<<endl;
	  itor++;
    } 
	ConfigParser::release();
	return 0;
}
