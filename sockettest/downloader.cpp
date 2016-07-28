/*
#include <string>
#include "socket.h"
#include "epollmanager.h"


using namespace std;

class Downloader
{
public:
	Downloader();
	~Downloader();
	httpQuest(StructUrl *p_url);
	httpRespose();
private:
	Socket m_socket;
	EpollManager m_epoll_manager;

};
*/

Downloader::Downloader()
{
	m_socket = new Socket();
	m_epoll_manager = new EpollManager();
}

Downloader::~Downloader()
{

}


int Downloader::httpQuest(StructUrl *p_url)
{
	m_socket->bulidConnect(p_url,PORT);
	m_socket->setNonblocking(m_socket->m_socket_handle);
    m_socket->request(m_socket->m_socket_handle,p_url);
}

int Downloader::httpRespose(int connectfd,char *rev_data)
{
	int n = 0,nread;
	while ((nread = read(connectfd, rev_data + n, BUFSIZ-1)) > 0) {
	    n += nread;
	}
	if (nread == -1 && errno != EAGAIN) 
	{
	    perror("read error");
	    m_epoll_manager->unregisHandle(connectfd);   
	}
}