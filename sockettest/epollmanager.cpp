#include "epollmanager.h"
#include <stdlib.h>
#include <stdio.h>

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

int EpollManager::wait()
{
	int ret = epoll_wait(m_epoll_handle,ready_event,OPEN_MAX,-1);
	if(ret == -1)
		p_err("epoll_wait");
	else
		return ret;
}