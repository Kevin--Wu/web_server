#include "common.h"

#include "EventLoop.h"

EventLoop *g_pLoop;

void *ThreadFun(void *args)
{
    g_pLoop->Loop();
    return NULL;
}

int main()
{
    EventLoop loop;
    g_pLoop = &loop;

//    pthread_t nTid;
//    pthread_create(&nTid, NULL, &ThreadFun, NULL);

    ThreadFun(NULL);

    sleep(10);

    return 0;
}
