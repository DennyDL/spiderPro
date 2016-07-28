#ifndef _EPOLLMANAGER_H_
#define _EPOLLMANAGER_H_
#include <sys/epoll.h>
#define OPEN_MAX 2048 

class EpollManager
{
public:
	EpollManager(int num);//构造函数,初始化epoll.得到句柄,num表示最大任务数
	~EpollManager();

	//注册socket句柄
	void regisHandle(int handle);
	void unregisHandle(int handle);
	void wait();
	/* data */
private:
	void p_err(char* errStr);
public:
	struct epoll_event tmp_event,ready_event[OPEN_MAX];
private:
	int m_epoll_handle;
	int m_task_num;//抓取的最大任务数
};

#endif