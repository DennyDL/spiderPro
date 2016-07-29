#include "downloader.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

Downloader::Downloader()
{
	this->m_socket = new Socket();
}

Downloader::~Downloader()
{
	delete this->m_socket;
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
	/*成功执行时，返回所读取的数据量。失败返回-1，errno被设为以下的某个值   
			EAGAIN：打开文件时设定了O_NONBLOCK标志，并且当前没有数据可读取
			EBADF：文件描述词无效，或者文件不可读
			EFAULT：参数buf指向的空间不可访问
			EINTR：数据读取前，操作被信号中断
			EINVAL：一个或者多个参数无效
			EIO：读写出错
			EISDIR：参数fd索引的时目录*/
	int n = 0,nread;
	while ((nread = read(connectfd, rev_data + n, length-1)) > 0) {
	    n += nread;
	}
	if (nread == -1 && errno != EAGAIN) 
	{
	    perror("read error");   
	}
}