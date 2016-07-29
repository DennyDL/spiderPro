#include <list>
#include <string>

using namespace std;
class ConfigParser
{
	public:
		
		int loader(char* conf_filepath);//0: success ;1: failed
		//for single
		static ConfigParser* instance()
		{
			if(__self == NULL)
			{
				__self = new ConfigParser();
				return __self;
			}
			else
			{
				return __self;
			}
			
			
		}
		static void release()
		{
			if(__self != NULL)
			{
				delete __self;
				__self = NULL;
			}
			
		}
		
		//operations
		int getJobNum();
		char* getUrlSeed();
		int getDepth();
		int getLogLevel();
		char* getModulePath();
		list<string> getModuleNames();
		list<string> getFileTypes();
		
	private:
		//for single
		ConfigParser();
		static ConfigParser* __self;
	private:
		int job_num;
		char* seed;
		int depth;
		int log_level;
		char* module_path;
		list<string> module_name;
		list<string> file_type;
};

	 
