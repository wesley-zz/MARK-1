#include "stdio.h"
#include "pthread.h"

#include "utility.h"
#include "logger.h"

static int sum = 0;

pthread_mutex_t mutex;

void *pthread_process(void *agrc)
{
    int i = 0;
    for (i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{

    logger_init();

    pthread_t t1, t2;

    pthread_mutex_init(&mutex,NULL);

    MARK_DEBUG(DEBUG,"DEBUG here:%d",15);

    pthread_create(&t1, NULL, pthread_process, NULL);
    pthread_create(&t2, NULL, pthread_process, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    MARK_DEBUG(DEBUG,"sum=%d",sum);

    return 0;
}