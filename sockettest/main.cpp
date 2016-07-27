#include <iostream>
#include <list>
#include <string>
#include "urlManager.h"
using namespace std;
#include "socket.h"


#define PTHREAD_NUM 30
#define OPEN_MAX 2048
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 65535

int epfd;
int connectfd_ready;
pthread_t thread_tid[PTHREAD_NUM];
pthread_attr_t attr;
pthread_mutex_t connectfd_ready_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t connectfd_ready_cond = PTHREAD_COND_INITIALIZER;

void p_err(char* errStr)
{
	perror(errStr);
	exit(1);
}
void* thread_main(void* arg)
{
	int connectfd;
	char* rev_data;
	rev_data = (char*)malloc(BUFSIZE);
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
		int n = 0,nread;
		while ((nread = read(connectfd, rev_data + n, BUFSIZ-1)) > 0) {
		    n += nread;
		}
		if (nread == -1 && errno != EAGAIN) {
		    perror("read error");
		    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL,connectfd,NULL);
			if (ret == -1);
			//	return -1;
		}
		cout << rev_data <<endl;
	}

//	close(connectfd);
}

int thread_make(int i)
{
	int ret;
	ret = pthread_create(&thread_tid[i],&attr,thread_main,(void*)socket);
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
	string str_url3("http://www.163.com");
	string str_url4("http://www.ifeng.com/");
	string str_url5("https://www.taobao.com");
	string str_url6("http://www.qunar.com/?ex_track=auto_4ef180cc");
	string str_url7("http://cd.58.com/?utm_source=market&spm=b-31580022738699-pe-f-835.123duba_102");
	list<string> str_urls;
	str_urls.push_back(str_url5);
	str_urls.push_back(str_url6);
	str_urls.push_back(str_url7);
	
	struct epoll_event tmp_event,ready_event[OPEN_MAX];
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

	epfd = epoll_create(OPEN_MAX);
	if(epfd == -1)
		p_err("epoll_create");

	UrlManager *url_manager = new UrlManager();
	url_manager->addUrl(str_url1);
	url_manager->addUrl(str_url2);
	url_manager->addUrl(str_url3);
	url_manager->addUrl(str_url4);
	url_manager->addUrlList(str_urls);
	StructUrl *p_url = NULL;


	Socket *socket = new Socket();
	

	for(int i = 0;i<7;i++)
	{
	    
 /*     cout<< "url:" <<p_url->url<<endl;
        cout<< "state:"<<p_url->state<<endl;
        cout<< "depth:"<<p_url->depth<<endl;
        cout<< "protocal:"<<p_url->protocal<<endl;
        cout<< "siteName:"<<p_url->siteName<<endl;
        cout<< "get:"<<p_url->get<<endl;
        cout<< "fileType:"<<p_url->fileType<<endl;
        cout<< "fileName:"<<p_url->fileName<<endl;
        cout<< "path:"<<p_url->path<<endl;*/
        p_url = url_manager->getUrlFromQuque();
	    socket->bulidConnect(p_url,PORT);
	    socket->setNonblocking(socket->m_socket_handle);
        socket->request(socket->m_socket_handle,p_url); 
        tmp_event.events = EPOLLIN | EPOLLET;
		tmp_event.data.fd = socket->m_socket_handle;
		ret = epoll_ctl(epfd,EPOLL_CTL_ADD,socket->m_socket_handle,&tmp_event);	
		if(ret == -1)
			p_err("epoll_ctl0");


 /*     socket->request(socket->m_socket_handle,p_url);  
 		socket->responce(socket->m_socket_handle);
        socket->disConnect(socket->m_socket_handle);
        cout <<"++++++++++++++++++++++++++++++++++"<<endl;*/
	}
	int readyNum = 0;
	while(1)
	{
		readyNum = epoll_wait(epfd,ready_event,OPEN_MAX,-1);/* 阻塞*/
		if(readyNum == -1)
			p_err("epoll_wait");

		for(int i = 0;i < readyNum;i++)
		{
			if(!(ready_event[i].events & EPOLLIN))
				continue;
			
			pthread_mutex_lock(&connectfd_ready_mutex);
			connectfd_ready = ready_event[i].data.fd;
			pthread_cond_signal(&connectfd_ready_cond);
			pthread_mutex_unlock(&connectfd_ready_mutex);
		}

	}
	
	

	return 0;
}
