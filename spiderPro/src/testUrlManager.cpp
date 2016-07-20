#include <iostream>
#include <list>
#include <string>
#include "urlManager.h"
using namespace std;

int main()
{
	string str_url1("http://bbs.chinaunix.net");
	string str_url2("https://www.duba.com/static/images/public/20160719/42d51184f1649e32da7d2115b1a867c6.jpg");
	string str_url3("http://blog.sina.com.cn/s/blog_7cd557ad0101dls2.html");
	string str_url4("http://www.it168.com/itclub/");
	string str_url5("http://www.chinaunix.net/cpp/static/images/bk1_img_01.jpg");
	string str_url6("http://www.chinaunix.net/cpp/static/images/line530.png");
	string str_url7("http://www.chinaunix.net/cpp/static/images/line530.png");
	list<string> str_urls;
	str_urls.push_back(str_url5);
	str_urls.push_back(str_url6);
	str_urls.push_back(str_url7);
	UrlManager *url_manager = new UrlManager();
	url_manager->addUrl(str_url1);
	url_manager->addUrl(str_url2);
	url_manager->addUrl(str_url3);
	url_manager->addUrl(str_url4);
	url_manager->addUrlList(str_urls);
	StructUrl *p_url = NULL;

	for(int i = 0;i<6;i++)
	{
	    p_url = url_manager->getUrlFromQuque();
        cout<< "url:" <<p_url->url<<endl;
        cout<< "state:"<<p_url->state<<endl;
        cout<< "depth:"<<p_url->depth<<endl;
        cout<< "protocal:"<<p_url->protocal<<endl;
        cout<< "siteName:"<<p_url->siteName<<endl;
        cout<< "fileType:"<<p_url->fileType<<endl;
        cout<< "fileName:"<<p_url->fileName<<endl;
        cout<< "path:"<<p_url->path<<endl;

        cout <<"++++++++++++++++++++++++++++++++++"<<endl;
	}

	return 0;
}
