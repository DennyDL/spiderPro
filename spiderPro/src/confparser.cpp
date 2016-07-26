#include "confparser.h"
#include "qstring.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#define INF 0x7FFFFFF
#define MAX_CONF_LEN 100



ConfigParser::ConfigParser()
{
	job_num = 10;
	seed = NULL;
	depth = 0;
	log_level = 0;
	module_path = NULL;	
}

int ConfigParser::loader(char* conf_filepath) 
{
	FILE *fp = NULL;
	char buf[MAX_CONF_LEN+1];
	int argc = 0;
	char **argv = NULL;
	int linenum = 0;
	char *line = NULL;
	const char *err = NULL;

	if ((fp = fopen(conf_filepath, "r")) == NULL) {
//		SPIDER_LOG(SPIDER_LEVEL_ERROR, "Can't load conf_file %s", CONF_FILE);
		return 1;
	} 

	/*
		原型  char *  fgets(char * s, int n,FILE *stream);
    参数：
         s: 字符型指针，指向存储读入数据的缓冲区的地址。
         n: 从流中读入n-1个字符
         stream ： 指向读取的流。
   返回值：
          1. 当n<=0 时返回NULL，即空指针。
          2. 当n=1 时，返回空串"".
          3. 如果读入成功，则返回缓冲区的地址。
          4. 如果读入错误或遇到文件结尾(EOF)，则返回NULL.
		*/
	conferr:
	while (fgets(buf, MAX_CONF_LEN+1, fp) != NULL) {
		linenum++;
		line = strim(buf);//去掉字符序列左边和右边的空格，如字符串

		if (line[0] == '#' || line[0] == '\0') continue;

		argv = strsplit(line, '=', &argc, 1);
		if (argc == 2) {
			/*
			头文件：#include <string.h>

			定义函数：int strcasecmp (const char *s1, const char *s2);

			函数说明：strcasecmp()用来比较参数s1 和s2 字符串，比较时会自动忽略大小写的差异。

			返回值：若参数s1 和s2 字符串相同则返回0。s1 长度大于s2 长度则返回大于0 的值，s1 长度若小于s2 长度则返回小于0 的值。

			范例
			#include <string.h>
			main(){
				char *a = "aBcDeF";
				char *b = "AbCdEf";
				if(!strcasecmp(a, b))
				printf("%s=%s\n", a, b);
			}

			执行结果：
			aBcDeF=AbCdEf
			
			1.函数原型：

			#include <string.h>
			char *strdup(const char *s); 
			2.功能：

			strdup()函数主要是拷贝字符串s的一个副本，
			由函数返回值返回，这个副本有自己的内存空间，和s没有关联。strdup函数复制一个字符串，使用完后，
			要使用delete函数删除在函数中动态申请的内存，strdup函数的参数不能为NULL，一旦为NULL，就会报段错误，因为该函数包括了strlen函数，
			而该函数参数不能是NULL。
			*/
				
			
			if (strcasecmp(argv[0], "max_job_num") == 0) {
				this->job_num = atoi(argv[1]);
			} else if (strcasecmp(argv[0], "seeds") == 0) {
				this->seed = strdup(argv[1]);
			} else if (strcasecmp(argv[0], "module_path") == 0) {
				this->module_path = strdup(argv[1]);
			} else if (strcasecmp(argv[0], "load_module") == 0) {
				this->module_name.push_back(strdup(argv[1]));
			} else if (strcasecmp(argv[0], "log_level") == 0) {
				this->log_level = atoi(argv[1]);
			} else if (strcasecmp(argv[0], "max_depth") == 0) {
				this->depth = atoi(argv[1]);
			} else if (strcasecmp(argv[0], "accept_types") == 0) {
				this->file_type.push_back(strdup(argv[1]));
			} else {
				err = "Unknown directive"; goto conferr;
			}
		} else {
			err = "directive must be 'key=value'"; goto conferr;
		}

	}
	return 0;

	
}

int ConfigParser::getJobNum()
{
	return job_num;
}

char* ConfigParser::getUrlSeed()
{
	return seed;	
}

int ConfigParser:: getDepth()
{
	return depth;
}

int ConfigParser::getLogLevel()
{
	return log_level;
}

char* ConfigParser::getModulePath()
{
	return module_path;
}

list<string> ConfigParser::getModuleNames()
{
	return module_name;
}

list<string> ConfigParser::getFileTypes()
{
	return file_type;
}



