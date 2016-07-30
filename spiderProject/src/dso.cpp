#include "dso.h"
#include "qstring.h"
#include <dlfcn.h>
int DsoManager::load(char* path,const char*name)
{
	Module *module  = new Module();
	char * npath = strcat2(3, path, name, ".so");

	void* handle = dlopen(npath,RTLD_GLOBAL | RTLD_NOW);
	if(handle == NULL)
		return MODULE_ERR;

	void *rv = (dlsym(handle,name));
	if(rv == NULL)
        return MODULE_ERR;


//	dlclose(handle);
	module = (Module *)rv;//module结构体的入口
//	module->init();//调用初始化函数
//暂时不需要init（）;找到module入口地址就可以了

	this->m_modules.insert(pair<string,Module*>(name,module));//插入管理的map中以便以后查询找到快速找到相应的模块入口地址

	return MODULE_OK;

}

Module* DsoManager::getModule(char* name)
{
	map<string, Module*>::iterator itor = this->m_modules.find(name);
	if(itor != m_modules.end())
	{
		return itor->second;
	}
	else
	{
		return NULL;
	}
}
