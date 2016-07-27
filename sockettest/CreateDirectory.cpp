#include <stdlib.h>  
#include <string.h> 
#include <unistd.h>
#include <stdarg.h>  
#include <sys/stat.h> 
#include <errno.h> 
#include <stdio.h>
int CreateDirectory(const char *sPathName )  
{  
    char DirName[256];      
    strcpy(DirName,sPathName);      
    int i,len = strlen(DirName);      
    if(DirName[len-1]!='/')      
    strcat(DirName,"/");            
    len = strlen(DirName);      
    for(i=1;i<len;i++)      
    {      
        if(DirName[i]=='/')      
        {      
            DirName[i] = 0;      
            if(access(DirName,NULL) != 0)      
            {      
                if(mkdir(DirName,0777) == -1)      
                {       
                    perror("mkdir error");       
                    return -1;       
                }      
            }    
            DirName[i] = '/';      
         }      
  }        
  return 0;      
}   
