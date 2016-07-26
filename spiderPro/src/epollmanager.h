#include <epoll.h>


class EpollManager
{
public:
	EpollManager(int num);//构造函数,初始化epoll.得到句柄,num表示最大任务数
	~EpollManager();

	//注册socket句柄
	int regisHandle(int handle);
	int unregisHandle(int handle);
	/* data */

private:
	int m_epoll_handle;
	int m_task_num;//抓取的最大任务数
};