#include "epollmanager.h"
/*
class EpollManager
{
public:
	EpollManager(int num);//构造函数,初始化epoll.得到句柄,num表示最大任务数
	~EpollManager();

	//注册socket句柄
	int regisHandle(int handle);
	int unregisHandle(int handle);

private:
	int m_epoll_handle;
	int m_task_num;//抓取的最大任务数
};
*/
void EpollManager::p_err(char* errStr)
{
	perror(errStr);
	exit(1);
}

EpollManager::EpollManager(int num)
{
	m_task_num = num;
	m_epoll_handle = epoll_create(OPEN_MAX);
	if(m_epoll_handle == -1)
		p_err("epoll_create");

}

EpollManager::~EpollManager()
{

}

void EpollManager::regisHandle(int handle)
{
	tmp_event.events = EPOLLIN | EPOLLET;
	tmp_event.data.fd = handle;
	int ret = epoll_ctl(m_epoll_handle,EPOLL_CTL_ADD,handle,&tmp_event);	
	if(ret == -1)
		p_err("EPOLL_CTL_ADD");
}

void EpollManager::unregisHandle(int handle)
{
	int ret = epoll_ctl(m_epoll_handle, EPOLL_CTL_DEL,handle,NULL);
	if (ret == -1)
		p_err("EPOLL_CTL_DEL");
}

void EpollManager::wait()
{
	int ret = epoll_wait(m_epoll_handle,ready_event,OPEN_MAX,-1);
	if(ret == -1)
		p_err("epoll_wait");
}