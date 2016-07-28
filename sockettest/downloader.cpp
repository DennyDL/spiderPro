#include "downloader.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

Downloader::Downloader()
{
	this->m_socket = new Socket();
	this->m_epoll_manager = new EpollManager(40);
}

Downloader::~Downloader()
{

}


int Downloader::httpQuest(StructUrl *p_url)
{
	m_socket->bulidConnect(p_url,PORT);
	m_socket->setNonblocking(m_socket->m_socket_handle);
    m_socket->request(m_socket->m_socket_handle,p_url);
    return m_socket->m_socket_handle;
}

void Downloader::httpRespose(int connectfd,char *rev_data,int length)
{
	int n = 0,nread;
	while ((nread = read(connectfd, rev_data + n, length-1)) > 0) {
	    n += nread;
	}
	if (nread == -1 && errno != EAGAIN) 
	{
	    perror("read error");
	    m_epoll_manager->unregisHandle(connectfd);   
	}
}