#include "stdio.h"

#define MARK_DEBUG(level,format, arg...) log_printf( __FILE__,__FUNCTION__, __LINE__, level, format, ##arg)

typedef enum DEBUG_LEVEL
{
    DEBUG = 1,
    WRAN,
    ERROR,
    SYSTERM_ERROR,
}DEBUG_LEVEL_E;

/**
 * @brief logger initialization
 * 
 * @return int 
 */
int logger_init(void);

void log_printf(const char *file,const char *func,const int line, int level, char *fmt,...);
