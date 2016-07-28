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
	httpRespose(int connectfd,char *rev_data);
private:
	Socket *m_socket;
	EpollManager *m_epoll_manager;

};