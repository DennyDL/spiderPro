#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
char* getTime()
{

	struct timeval start, end;
    	gettimeofday( &start, NULL );
    	printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
	char *str_time = malloc(25);
	sprintf(str_time,"%d.%d",start.tv_sec,start.tv_usec);
	return str_time;
}
