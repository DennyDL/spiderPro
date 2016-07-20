#include "url.h"

Url::Url()//构造函数
{
	this->m_url.state = 0;
	this->m_url.depth = 1;
}

int Url::parseUrl(string url)  //解析url，并填充内部URL结构
{
	this->m_url.url = url;
	this->m_url.protocal = getProtocal(url);//利用字符串操作函数进行解析
	this->m_url.siteName = getSiteName(url);
	this->m_url.fileType = getFileType(url);
	this->m_url.fileName = getFileName(url);
	this->m_url.path = getPath(url);
}


string Url::getProtocal(string str_url)
{
	string str("");
	int n = str_url.find("://",0);
	if(n == string::npos)
	{
		return str;
	}

	return str_url.substr(0,n);
}

string Url::getSiteName(string str_url)
{
	string str("");
	int n = str_url.find("://",0);
	if(n == string::npos)
	{
		return str;
	}
	int n1 = str_url.find("/",n + 4);
	if(n1 == string::npos)
	{
		return str_url.substr(n+3,n1);
	}
	return str_url.substr(n+3,n1-(n+3));
}

string Url::getFileType(string str_url)
{
	string str("");
	if(getPath(str_url) == str)
	{
	    return str;
	}
	int n = str_url.rfind(".",string::npos);
	if(n == string::npos)
	{
		return str;
	}
	int n1 = str_url.length();
	if(n1 == string::npos)
	{
		return str;
	}
	return str_url.substr(n+1,n1-n);
}

string Url::getFileName(string str_url)
{

	string str("");
	if(getPath(str_url) == str)
	{
	    return str;
	}
	int n = str_url.rfind(".",string::npos);
	if(n == string::npos)
	{
		return str;
	}
	int n1 = str_url.rfind("/",n);
	if(n1 == string::npos)
	{
		return str;
	}
	return str_url.substr(n1+1,n-n1-1);
}

string Url::getPath(string str_url)
{
	string str("");
	string siteName = getSiteName(str_url);
	int n = str_url.find(siteName,0);
	if(n == string::npos)
	{
		return str;
	}
	n = n + siteName.length();
	int n1 = str_url.rfind("/",string::npos);
	if(n1 == string::npos)
	{
		return str;
	}
	return str_url.substr(n,n1-n+1);
}

StructUrl* Url::getUrlData()
{
	return &m_url;
}
