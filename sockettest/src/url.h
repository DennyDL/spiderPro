#ifndef _URL_H_
#define _URL_H_

#include <iostream>
#include <string>
using namespace std;

struct StructUrl
{
	string url;
	string protocal;
	string siteName;//域名，网站名
	string get;//get请求参数
	string path;
	string fileName;
	int state;
	int depth;
	string fileType;
};

class Url
{
public:
	Url();//构造函数
	int parseUrl(string str_url);  //解析url，并填充内部URL结构,通过构造函数可以传入完整url到m_url中,那么解析函数就可以直接使用,所以不需要给解析函数传递url字符串
	StructUrl* getUrlData();
private:
	string getProtocal(string str_url);
	string getSiteName(string str_url);
	string getPath(string str_url);
	string getFileType(string str_url);
	string getFileName(string str_url);
	string getGet(string str_url);
	StructUrl m_url;
};
#endif
