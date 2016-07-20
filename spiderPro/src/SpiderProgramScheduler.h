#ifndef SPS_H
#define SPS_H
#include <>


class SpiderProgramScheduler
{
public:
	SpiderProgramScheduler();
	~SpiderProgramScheduler();
	/* data */
public://业务成员函数
	int init(int argc,char* argv[]);//初始化环境,返回值:1 成功 ,0 失败
	int daemon();//以守护进程方式运行,返回值:1 成功 ,0 失败
	int run();//主处理模块,返回值:1 成功 ,0 失败

private://内部接口，以私有函数出现，不能被主业务流程之外的模块调用
	int handleArgv(int argc,char* argv[]);//处理传入参数

private://定义私有成员变量
	bool isDaemon;

};

#endif

