#ifndef _DOWNLOADER_H_
#define _DOWNLOADER_H_
#include <string>
#include "socket.h"
#include "epollmanager.h"


using namespace std;

class Downloader
{
public:
	Downloader();
	~Downloader();
	void httpQuest(StructUrl *p_url);
	void httpRespose(int connectfd,char *rev_data/*out*/,int length);
private:
	Socket *m_socket;
	EpollManager *m_epoll_manager;

};
#endif