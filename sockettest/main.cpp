#include <iostream>
#include <list>
#include <map>
#include <string>
#include "urlManager.h"
#include "socket.h"
#include "downloader.h"
#include "epollmanager.h"
using namespace std;

#define PTHREAD_NUM 30
#define OPEN_MAX 2048
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "getTime.h"
#include "CreateDirectory.h"
#include "dso.h"
#define BUFSIZE 65535

int connectfd_ready;
map<int,string> fd_path_map;
pthread_t thread_tid[PTHREAD_NUM];
pthread_attr_t attr;
pthread_mutex_t connectfd_ready_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t connectfd_ready_cond = PTHREAD_COND_INITIALIZER;

Downloader *download = new Downloader();
EpollManager* epollmanager = new EpollManager(50);
DsoManager *dso_manager = new DsoManager();


void p_err(char* errStr)
{
	perror(errStr);
	exit(1);
}
void* thread_main(void* arg)
{
	int connectfd;
	//char rev_data[BUFSIZE];
	HandleData handle_data;
	char* rev_data = (char*)malloc(BUFSIZE);
	memset(rev_data,0,BUFSIZE);
	while(1)
	{
		pthread_mutex_lock(&connectfd_ready_mutex);
		pthread_cond_wait(&connectfd_ready_cond,&connectfd_ready_mutex);//可能当用crtl+c终止掉客户端程序时，使epoll监控的fd激活两次，从而使两个线程读取相同的fd，就会造成先close（fd）再删除epoll事件。就会出错，bad fd，为防止两个线程同时读取相同的fd，使用该标志位来做一个判断
		connectfd = connectfd_ready;
		pthread_mutex_unlock(&connectfd_ready_mutex);
		/*成功执行时，返回所读取的数据量。失败返回-1，errno被设为以下的某个值   
			EAGAIN：打开文件时设定了O_NONBLOCK标志，并且当前没有数据可读取
			EBADF：文件描述词无效，或者文件不可读
			EFAULT：参数buf指向的空间不可访问
			EINTR：数据读取前，操作被信号中断
			EINVAL：一个或者多个参数无效
			EIO：读写出错
			EISDIR：参数fd索引的时目录*/
		 
		
		//if(itor != fd_path_map.end())
		//char* path = (itor->second).c_str();
		download->httpRespose(connectfd,rev_data,BUFSIZE);
		
		map<int,string>::iterator itor = fd_path_map.find(connectfd);
		if(itor != fd_path_map.end())
		{
			handle_data.data = rev_data;
			handle_data.path = (itor->second).c_str();
			Module* module = dso_manager->getModule("savehtml");
			if(module != NULL)
    			module->handle((void *)&handle_data);
		}
	
		
		//cout << rev_data <<endl;
	}

//	close(connectfd);
}

int thread_make(int i)
{
	int ret;
	ret = pthread_create(&thread_tid[i],&attr,thread_main,NULL);
	if(ret != 0)
	{
		p_err("pthread_create");
	}
	return thread_tid[i];
}

int main()
{
	string str_url1("http://www.baidu.com");
	string str_url2("http://www.qq.com");
	string str_url3("http://blog.csdn.net/yusiguyuan/article/details/21478577");
	string str_url4("http://www.ifeng.com");
	string str_url5("http://www.xinhuanet.com");
	string str_url6("http://www.sina.com.cn");
	string str_url7("http://bbs.csdn.net");
	list<string> str_urls;
	str_urls.push_back(str_url5);
	str_urls.push_back(str_url6);
	str_urls.push_back(str_url7);
	
	if(dso_manager->load("./","savehtml"))
    	cout << "load success !"<<endl;
    

	int ret = pthread_attr_init(&attr);
	if(ret != 0)
		p_err("pthread_attr_init");
	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if(ret != 0)
		p_err("pthread_attr_setdetachstate");

	int tmp_tid;
	for(int i = 0;i < PTHREAD_NUM;i++)
	{
		tmp_tid = thread_make(i);
		printf("create thread id is :%d\n",tmp_tid);
	}


	UrlManager *url_manager = new UrlManager();
	url_manager->addUrl(str_url1);
	url_manager->addUrl(str_url2);
	url_manager->addUrl(str_url3);
	url_manager->addUrl(str_url4);
	url_manager->addUrlList(str_urls);
	StructUrl *p_url = NULL;

	string str_path;
	for(int i = 0;i<7;i++)
	{
        p_url = url_manager->getUrlFromQuque();
	    int sockfd = download->httpQuest(p_url);

        str_path="/home/denny/download/";
        str_path.append(p_url->siteName);
        str_path.append("/");
        if(CreateDirectory(str_path.c_str()) == -1)
        	cout<<"CreateDirectory err"<<endl;

        char* str_time = getTime();
        str_path.append(str_time);
        free(str_time);
        cout<<"fd:"<<sockfd<<"path"<<str_path<<endl;
        fd_path_map.insert(pair<int,string>(sockfd,str_path));
        
        epollmanager->regisHandle(sockfd);
	}
	int readyNum = 0;
	while(1)
	{
		readyNum = epollmanager->wait();/* 阻塞*/
		if(readyNum == -1)
			p_err("epoll_wait");

		for(int i = 0;i < readyNum;i++)
		{
			if(!(epollmanager->ready_event[i].events &EPOLLIN))
				continue;
			sleep(1);
			pthread_mutex_lock(&connectfd_ready_mutex);
			connectfd_ready = epollmanager->ready_event[i].data.fd;
			pthread_cond_signal(&connectfd_ready_cond);
			pthread_mutex_unlock(&connectfd_ready_mutex);
		}

	}

	return 0;
}
