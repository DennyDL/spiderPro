#include <iostream>
#include <list>
#include <map>
#include <string>
#include "urlManager.h"
#include "socket.h"
#include "downloader.h"
#include "epollmanager.h"
#include "dso.h"
#include "confparser.h"//在confparser.cpp也包含了confparser.h，所以注意不要重复定义

#define CONF_PATH "../spider.conf"
ConfigParser* ConfigParser::__self = NULL;//放在confparser.h会出现重复定义，注意，static是在编译阶段就分配内存
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
ConfigParser* cp = ConfigParser::instance();
UrlManager *url_manager = new UrlManager();

void p_err(char* errStr)
{
	perror(errStr);
	exit(1);
}

void* getUrlFromQuque(void* arg)
{
	string str_path;
	StructUrl *p_url = NULL;
	while(1)
	{
        if(!(url_manager->m_url_quque).empty())
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
        else
        {
        	sleep(0.5);
        }
        
	}
}

void* thread_main(void* arg)
{
	int connectfd;
	int page_num = -1;
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
		
		download->httpRespose(connectfd,rev_data,BUFSIZE);
		
		map<int,string>::iterator itor = fd_path_map.find(connectfd);
		if(itor != fd_path_map.end())
		{
			handle_data.data = rev_data;
			handle_data.path = (itor->second).c_str();

			Module* module = dso_manager->getModule("savehtml");
			if(module != NULL)
    			page_num = module->handle((void *)&handle_data);
    		if(page_num == 0)
    		{
    			epollmanager->unregisHandle(connectfd);
    			fd_path_map.erase(connectfd);
    		}
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
	cp->loader(CONF_PATH);
	list<string> module_name = cp->getModuleNames();
	list<string>::iterator itor_list = module_name.begin();
	while(itor_list!=module_name.end())
    {
	  if(dso_manager->load(cp->getModulePath(),(*itor_list).c_str()))
    	cout << "load success !"<<endl;
	  itor_list++;
    }
     
	url_manager->addUrl(cp->getUrlSeed());

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

	
	
	pthread_t get_url_thread_tid;
	ret = pthread_create(&get_url_thread_tid,&attr,getUrlFromQuque,NULL);
	if(ret != 0)
	{
		p_err("pthread_create");
	}
	printf("create get_url_thread_tid is :%d\n",get_url_thread_tid);
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
