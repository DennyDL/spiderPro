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
bool getUrl(list<string> &str_urls,char *buf)
{
	if(buf == NULL)
		return false;
	cout <<"**************getUrl1***************"<<endl;
	int status,i;
	int cflags = REG_EXTENDED;
	regmatch_t  pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;
	const char* pattern = "href=\"http://[^\"]*";//href=\"http://.*\"[a-zA-z]+://[^\\s]*
	
	regcomp(&reg,pattern,cflags);
	cout <<"**************getUrl2***************"<<endl;
	char *p = buf;
	char des[2560];
	while(!regexec(&reg,p,nmatch,pmatch,0))
	{	
		cout <<"**************getUrl3***************"<<endl;
		substr(p,des,pmatch[0].rm_so+6,pmatch[0].rm_eo);
		cout <<"**************getUrl4***************"<<endl;
		string str_url(des);
		cout <<"**************getUrl5***************"<<endl;
		cout <<str_url <<endl;
		str_urls.push_back(str_url);
		cout <<"**************getUrl6***************"<<endl;
		p += pmatch[0].rm_eo;

		if(!*p)break;
		
	}
	regfree(&reg);
	return true;
}