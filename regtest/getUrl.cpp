#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <iostream>
#include "getUrl.h"
using namespace std;
char* substr(char*str,char* des,unsigned start, unsigned end)
{
	unsigned n = end - start;

	strncpy(des, str + start, n);

	des[n] = 0;

	return des;

}
void getUrl(list<string> &str_urls,char *buf)
{
	int status,i;
	int cflags = REG_EXTENDED;
	regmatch_t  pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;
	const char* pattern = "http://[^\"]*";//href=\"http://.*\"[a-zA-z]+://[^\\s]*
	
	regcomp(&reg,pattern,cflags);

	char *p = buf;
	char des[256];
	while(!regexec(&reg,p,nmatch,pmatch,0))
	{	
		substr(p,des,pmatch[0].rm_so,pmatch[0].rm_eo);
		
		string str_url(des);
		
		str_urls.push_back(str_url);
		
		p += pmatch[0].rm_eo;

		if(!*p)break;
		
	}
	regfree(&reg);
		
}
