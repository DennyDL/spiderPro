/*程序的主函数 */
#include "SpiderProgramScheduler.h"
#include "spider.h"

int main(int argc,char *argv[])
{
    /*实例化一个调度模块*/
	SpiderProgramScheduler spiderProSch = new SpiderProgramScheduler();
	//3、初始化环境
	/*
        3.1、通过参数控制是否以守护进程模式运行
        3.2、提供帮助信息
		3.3、读取配置文件，提取参数
		3.4、载入程序动态库
	*/
	if (spiderProSch.init(argc,argv) == 0)
	{
		//用SPIDER_LOG打印日志
		SPIDER_LOG(SPIDER_LEVEL_ERROR,"app init is failed ,app has exit!");
		return -1;
	}

	//4、开始程序主流程（控制模块）
	/*开始主业务流程*/
	/*
		4.1、将URL种子交给URL管理器。
		4.2、分析种子，得到URL IP地址（DNS解析）
		4.3、根据URL获取第一个页面资源
		4.4、对页面进行处理
			4.4.1 解析页面取得URL
			4.4.2、生成URL列表，交给URL管理器
			4.4.3、对页面进行持久化操作
		4.5、
		4.6、通过调用epoll框架产生新任务（先检测是否到达最大任务数，功能封装在独立的函数，循环添加，直到epoll监控的最大值）
			4.6.1、从URL管理器中取出一个URL
			4.6.2、利用URL的ip地址请求资源，将返回的socket句柄加入epoll监控树
		4.7、通过epoll_wait()监控事件，触发则，创建线程处理接收的数据（对页面进行处理4.4）	一直在这个地方循环，直到url处理队列已经清空
	*/
	if (spiderProSch.run() == 0)
	{
		SPIDER_LOG(SPIDER_LEVEL_ERROR,"main app has exception ,app has exit!");
		return -1;
	}

    return 0;
}

