#include <stdio.h>
#include <map>
#include <list>
#include <queue>
#include <string>
#include "url.h"
using namespace std;

class UrlManager
{
public:
	//外部接口
	int addUrl(string url_str); 				//添加一个全新的URL 加入到list and quque中，同时生存索引
	int addUrlList(list<string> url_strs); 		//批量添加
	StructUrl* getUrlFromQuque();  				//取一个未处理的URL结构体指针
	int setUrlSuccessState(StructUrl* url); 			//设置URL处理状态,可能会调用removeUrlFromQuque(),因为如果状态为已经成功抓取,就应该移除该url
	int setUrlFailedState(StructUrl* url);
private: //内部接口
	bool findUrl(string url_str);				//该URL是否已经在

private:

	map <string, StructUrl*> m_url_map;  				//string 是url字符串，map会用哈希算法计算出hashcode，建立所有URL的索引
	queue<StructUrl*>  m_url_quque;   					//维护等待抓取的URL

};
