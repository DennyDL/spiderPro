#include <string>
#include "url.h"
#define PORT 80


class Socket//得到完整的数据
{
public:
	Socket();
	~Socket();

	int request(int fd, StructUrl* url);//请求连接
	int responce();//接收反馈
	void* getData();//获取返回的数据
	int setSockket(int fd);//设置socket
	int bulidConnect(StructUrl* url,int port);//建立连接
	int disConnect(int fd);//断开连接

private:
	int m_socket_handle;//socket句柄
	char* buf;
	/* data */
};

