#include <iostream>
#include "getUrl.h"
using namespace std;


int main()
{
	char* rev_data = "<link href=\"http://y1.ifengimg.com/index/72x72_2520ifeng.png\" rel=\"apple-touch-icon\"/> <<link href=\"http://y3.ifengimg.com/index/72x72_2520ifeng.png\" rel=\"apple-touch-icon\"/>>";	
	list<string> str_urls;
	getUrl(str_urls,rev_data);
	list<string>::iterator itor = str_urls.begin();
	while(itor != str_urls.end())
	{
		cout << *itor <<endl;
		itor++;
	}
	return 0;
}
