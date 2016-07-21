/*程序的主函数 */
#include "SpiderProgramScheduler.h"
#include "spider.h"



int main(int argc,char* argv[])
{
	/*实例化一个调度模块*/
	SpiderProgramScheduler spiderProSch = new SpiderProgramScheduler();

	/*初始化*/
	if (spiderProSch.init(argc,argv) == 0)
	{
		//用SPIDER_LOG打印日志
		SPIDER_LOG(SPIDER_LEVEL_ERROR,"app init is failed ,app has exit!");
		return -1;
	}

	/*开始主业务流程*/
	if (spiderProSch.run() == 0)
	{
		SPIDER_LOG(SPIDER_LEVEL_ERROR,"main app has exception ,app has exit!");
		return -1;
	}

	return 0;
}