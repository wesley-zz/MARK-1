// #include "stdio.h"
// #include "pthread.h"
#include <string.h>  
#include <errno.h>  
#include <stdio.h>  
#include <stdint.h>  
#include <stddef.h>  
#include <stdlib.h>  
#include <sys/stat.h>  
#include <sys/types.h> 
#include <stdarg.h>
#include <stdbool.h>
#include <sys/un.h>
#include <sys/param.h>
#include <time.h> 
#include "logger.h"

/**
 * @brief logger initialization
 * 
 * @return int 
 */
int logger_init(void)
{
	MARK_DEBUG(DEBUG,"logger init now");
	return 0;
}

/**
 * @brief Get the commonlog time object
 * 
 * @return char* 
 */
char *get_commonlog_time(void)
{
	char *p;
	char sys_time[64];	
	time_t tnow = time(NULL);	
	struct tm *ptm = localtime(&tnow);
	
	memset(sys_time, 0 ,sizeof(sys_time));
	sprintf(sys_time, "%04d-%02d-%02d][%02d:%02d:%02d]",ptm->tm_year+1900 ,ptm->tm_mon+1 ,ptm->tm_mday ,ptm->tm_hour ,ptm->tm_min ,ptm->tm_sec);
	//return (char *)sys_time;
	p = sys_time;
	return p;
}

/**
 * @brief print log message
 * 
 * @param file print the logger file
 * @param func print the logger function
 * @param line print the logger line
 * @param level print the logger level
 * @param fmt print the logger format
 * @param ... print the logger content
 */
void log_printf(const char *file,const char *func,const int line, int level, char *fmt,...)
{
	// if(real_debug_level & level)
	if(level > DEBUG)
	{
		char msg_buf[20*1024];
		va_list ap;
		va_start(ap,fmt);
		sprintf(msg_buf,"[%s[%s][%s][%d]:",get_commonlog_time(),file,func,line);
		vsprintf(msg_buf+strlen(msg_buf),fmt,ap);
		fprintf(stderr,"%s\n",msg_buf);		
		va_end(ap);
	}
	else
	{
		char msg_buf[20*1024];
		va_list ap;
		va_start(ap,fmt);
		sprintf(msg_buf,"[%s:",get_commonlog_time());
		vsprintf(msg_buf+strlen(msg_buf),fmt,ap);
		fprintf(stderr,"%s\n",msg_buf);		
		va_end(ap);
	}
}