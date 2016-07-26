#include "socket.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#define BUFSIZE 65535
/*
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
	int connect(int fd,string ip,int port);//建立连接
	int disConnect(int fd);//断开连接

private:
	int m_socket_handle;//socket句柄
	char* buf;
	
};
*/
Socket::Socket()
{

}

Socket::~Socket()
{
	
}

int Socket::request(int fd, StructUrl* url)
{
	char request[BUFSIZE];
	this->m_get = url->get.c_str();
	//向WEB服务器发送URL信息
    memset(request,0,BUFSIZE);
    strcat(request,"GET ");
    strcat(request,this->m_get);
    strcat(request," HTTP/1.1\r\n");//至此为http请求行的信息
    strcat(request,"Accept:*/*\r\n");
    strcat(request,"HOST: ");
    strcat(request,this->m_host);
    strcat(request,"\r\n");
    strcat(request,"Connection: Keep-Alive\r\n");
    strcat(request,"\r\n");
    //strcat(request,"Accept-Lauguage: zh-CN,zh;q=0.8\r\n");
    //strcat(request,"Accept-Encoding: x-gzip, x-deflate, gzip, deflat\r\n");
    //strcat(request,"Accept-charset: utf-8, utf-8; q=0.5, *; q=0.5\r\n"); 
    //strcat(request,"Content-Type: text/html\r\n");
    //strcat(request,"Content-Length: 1024\r\n");
    //strcat(request,"Cache-Control: no-cache\r\n\r\n");
	
	cout << request <<endl;

	int ret = write(fd,request,strlen(request));
    if (ret < 0)
    {
            printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
            return -1;
    }else
    {
            printf("消息发送成功，共发送了%d个字节！\n\n", ret);
    }

}

int Socket::responce(int fd)
{
	fd_set   t_set1;
    struct timeval  tv;
    int h,i;
	this->m_buf = (char*)malloc(BUFSIZE);
	memset(m_buf,0,BUFSIZE);
	
	FD_ZERO(&t_set1);
    FD_SET(fd, &t_set1);
	while(1)
	{
        sleep(2);
        tv.tv_sec= 0;
        tv.tv_usec= 0;
        h= 0;
        printf("--------------->1");
        h= select(fd +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");

        //if (h == 0) continue;
        if (h < 0) {
                close(fd);
                printf("在读取数据报文时SELECT检测到异常，该异常导致线程终止！\n");
                return -1;
        };

        if (h > 0){
                memset(m_buf, 0, 4096);
                i= read(fd, m_buf, 4095);
                if (i==0){
                        close(fd);
                        printf("读取数据报文时发现远端关闭，该线程终止！\n");
                        return -1;
                }

                printf("%s\n", m_buf);
        }
    }
	return 0;
}


void* Socket::getData()
{
	return this->m_buf;
}

int Socket::setSockket(int fd)
{
	return 0;
}


int Socket::bulidConnect(StructUrl* url,int port)
{
	struct sockaddr_in serveraddr;
	struct hostent *pURL = NULL;
	this->m_socket_handle = socket(AF_INET,SOCK_STREAM,0);
	if(this->m_socket_handle < 0)
	{
		perror("socket err");
		return -1;
	}
	this->m_host = (url->siteName).c_str();
	pURL = gethostbyname(this->m_host);//将上面获得的主机信息通过域名解析函数获得域>名信息
	
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr_list[0]);
	char ipstr[128];
	inet_ntop(AF_INET,&serveraddr.sin_addr.s_addr,ipstr, sizeof(ipstr));
	cout <<"ip:"<<ipstr <<endl;
	int ret = connect(this->m_socket_handle,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(ret == -1)
	{
		perror("connect err");
		return -1;
	}
	cout <<"connect success"<<endl;
	return 0;
}

int Socket::disConnect(int fd)
{
	if(close(fd) == -1)
	{
		perror("close err");
		return -1;
	}
	else
		return 0;
}