#include <iostream>
#include "dso.h"

using namespace std;

int main()
{
    int argc = 4;
    DsoManager *dso_manager = new DsoManager();
    
    if(dso_manager->load("./","libtestmod"))
    	cout << "load success !"<<endl;
    Module* module = dso_manager->getModule("libtestmod");

    if(dso_manager->load("./","libtestmod1"))
    	cout << "load success 1!"<<endl;  
    Module* module1 = dso_manager->getModule("libtestmod1");
    if(module1 != NULL)
    	module1->handle((void *)argc);

    
    
    if(module != NULL)
    	module->handle((void *)argc);
    int count = 0;
    map<string, Module*>::iterator itor ;
	for(itor = dso_manager->m_modules.begin();itor != dso_manager->m_modules.end();itor++)
	{
		count++;
		cout << count <<endl;
		cout <<(Module*)itor->second->name << endl;
	}
	
    return 0;
}
