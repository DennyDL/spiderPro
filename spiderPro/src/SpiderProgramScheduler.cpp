#include "SpiderProgramScheduler.h"
#include "spider.h"
#include "confparser.h"

SpiderProgramScheduler::SpiderProgramScheduler()
{

}

SpiderProgramScheduler::~SpiderProgramScheduler()
{

}

int SpiderProgramScheduler::init(int argc,char* argv[])
{
	//处理参数,例如守护进程标识,赋值到isDaemon
	handleArgv(argc,argv);
	//读取配置文件
	ConfigParser* cp = ConfigParser::instance();
	cp->loader(CONF_PATH);

	//处理是否以守护进程运行
	if (isDaemon == true)
	{
		this->daemon();
	}

	//载入动态模块,等待完成
}

int SpiderProgramScheduler::run()
{
	//等待相关管理类的实现
}

int SpiderProgramScheduler::daemon()
{

}