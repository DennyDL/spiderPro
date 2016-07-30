#ifndef _DOWNLOADER_H_
#define _DOWNLOADER_H_
#include <string>
#include "socket.h"


using namespace std;

class Downloader
{
public:
	Downloader();
	~Downloader();
	int httpQuest(StructUrl *p_url);
	void httpRespose(int connectfd,char *rev_data/*out*/,int length);
private:
	Socket *m_socket;

};
#endif