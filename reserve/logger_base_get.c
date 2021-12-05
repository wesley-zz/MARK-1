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
 
//通过宏来控制是否打开日志输出
#ifdef DISABLE_DEBUG
#define real_debug_level 0
#else
#define real_debug_level debug_level
#endif
 
 
//定义日志输出级别
#define 	FATALEER    (1<<0)
#define 	ERROR       (1<<1)
#define 	WRAN        (1<<2)
#define 	INFO      (1<<3)
#define 	DEBUG    (1<<4) 
 
#define WriteLog(level,mesg) log_mesg_printf(__FILE__, __LINE__, __func__, level, mesg)
#define WriteLog2(level,format, arg...) log_mesg_printf2( __FILE__,__FUNCTION__, __LINE__, level, format, ##arg)
 
int debug_level = 0;
 
struct dbg {
    int level;
    const char *mesg;
};
 
static struct dbg debug_level_table[] = {
    {FATALEER, "Config The Log Level as FATALEER"},
    {ERROR, "Config The Log Level as ERROR"},
    {WRAN, "Config The Log Level as WRAN"},
    {INFO, "Config The Log Level as INFO"},
    {DEBUG, "Config The Log Level as DEBUG"}
};
 
void print_debug_usage(void)
{
    struct dbg *p;
 
    fprintf(stderr,
            "  To calculate the debug level, logically 'or'\n"
            "  some of the following values together to get a debug level:\n");
    for (p = debug_level_table;
         p <
         debug_level_table +
         (sizeof (debug_level_table) / sizeof (struct dbg)); p++) {
        fprintf(stderr, "\t%d:\t%s\n", p->level, p->mesg);
    }
    fprintf(stderr, "\n");
}
 
void parse_debug(char *foo)
{
    int i;
    struct dbg *p;
 
    if (!foo)
        return;
    fprintf(stderr, "Before parse_debug, debug_level is: %d\n",
            debug_level);
 
    i = atoi(foo);
    if(i == -1) 
	{
		/* error */
		fprintf(stderr, "Invalid level specified.\n");
		exit(0);
    }    
    for (p = debug_level_table;p < debug_level_table +(sizeof (debug_level_table) / sizeof (struct dbg)); p++)
	{
        if (i > 0) {
            if (i & p->level) {                
                fprintf(stderr, "Enabling %s debug level.\n",p->mesg);
                debug_level |= p->level;
            }
        } 
    }
    fprintf(stderr, "After parse_debug, debug_level is: %d\n",
            debug_level);
}
 
char *get_commonlog_time(void)
{
	char *p;
	char sys_time[64];	
	time_t tnow = time(NULL);	
	struct tm *ptm = localtime(&tnow);
	
	memset(sys_time, 0 ,sizeof(sys_time));
	sprintf(sys_time, "%04d-%02d-%02d %02d:%02d:%02d",ptm->tm_year+1900 ,ptm->tm_mon+1 ,ptm->tm_mday ,ptm->tm_hour ,ptm->tm_min ,ptm->tm_sec);
	//return (char *)sys_time;
	p = sys_time;
	return p;
}
 
void log_mesg_printf(const char *file, int line, const char *func,int level, const char *mesg)
{
    if(real_debug_level & level)
	{
		int errno_save = errno;
		fprintf(stderr, "%s%s:%d (%s) - ", get_commonlog_time(), file, line, func);
		errno = errno_save;
		perror(mesg);
		errno = errno_save;
	}	  
}
 
void log_mesg_printf2(const char *file,const char *func,const int line, int level, char *fmt,...)
{
	if(real_debug_level & level)
	{
		char msg_buf[20*1024];
		va_list ap;
		va_start(ap,fmt);
		sprintf(msg_buf,"[%s  %s:%s:%d] ",get_commonlog_time(),file,func,line);
		vsprintf(msg_buf+strlen(msg_buf),fmt,ap);
		fprintf(stderr,"%s\n",msg_buf);		
		va_end(ap);
	}
}
 
// int main(int argc, char* argv[])
// {
	
// #ifdef DISABLE_DEBUG
// 	print_debug_usage();
// 	parse_debug(argv[1]);//解析日志打印输出级别
// #endif
// 	//不使用可变参数解析样例
// 	WriteLog(DEBUG,"I want to DEBUG");
// 	WriteLog(INFO,"I want to INFO");
// 	WriteLog(WRAN,"I want to WARN");
// 	WriteLog(ERROR,"I want to ERROR");
// 	WriteLog(FATALEER,"I want to FATALEER");
// 	//使用可变参数解析样例
// 	WriteLog2(DEBUG,"I want to %s which level is %d","DEBUG",DEBUG);
// 	WriteLog2(INFO,"I want to %s which level is %d","INFO",INFO);
// 	WriteLog2(WRAN,"I want to %s which level is %d","WRAN",WRAN);
// 	WriteLog2(ERROR,"I want to %s which level is %d","ERROR",ERROR);
// 	WriteLog2(FATALEER,"I want to %s which level is %d","FATALEER",FATALEER);
	
// 	return 0;
// }