#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main()
{
    string tmp,html;
    while(getline(std::cin,tmp))
    {
        tmp += '\n';
        html += tmp;
    }
    string pattern("http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    sregex_iterator it(html.begin(), html.end(), r);
    sregex_iterator end;
    for (;it != end;++it)
    {
        cout << it->str() << endl;
    }
}
