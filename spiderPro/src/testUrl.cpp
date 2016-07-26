#include <iostream>
#include <list>
#include <string>
#include "url.h"
using namespace std;

int main()
{
	string str_url("http://www.it168.com/itclub/");
	Url *url = new Url();
	url->parseUrl(str_url);
	StructUrl* p_url = url->getUrlData();
	cout<< "url:" <<p_url->url<<endl;
	cout<< "state:"<<p_url->state<<endl;
	cout<< "depth:"<<p_url->depth<<endl;
	cout<< "protocal:"<<p_url->protocal<<endl;
	cout<< "siteName:"<<p_url->siteName<<endl;
	cout<< "fileType:"<<p_url->fileType<<endl;
	cout<< "fileName:"<<p_url->fileName<<endl;
	cout<< "path:"<<p_url->path<<endl;
	return 0;
}
