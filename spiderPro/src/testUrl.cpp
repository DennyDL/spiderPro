#include <iostream>
#include <list>
#include <string>
#include "url.h"
using namespace std;

int main()
{
	string str_url("https://www.duba.com/static/images/public/20160719/42d51184f1649e32da7d2115b1a867c6.jpg");
	Url *url = new Url();
	url->parseUrl(str_url);
	StructUrl* p_url = url->getUrlData();
	cout<< p_url->url<<endl;
	cout<< p_url->state<<endl;
	cout<< p_url->depth<<endl;
	cout<< p_url->protocal<<endl;
	cout<< p_url->siteName<<endl;
	cout<< p_url->fileType<<endl;
	cout<< p_url->fileName<<endl;
	cout<< p_url->path<<endl;
	return 0;
}
