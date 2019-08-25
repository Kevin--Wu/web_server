#include "common.h"

#include "EventLoop.h"
#include "Channel.h"

EventLoop *g_pLoop;

void timeout()
{
    std::cout << "Time out" << std::endl;
    g_pLoop->Quit();
}

int main()
{
    EventLoop loop;
    g_pLoop = &loop;

    int nTimeFd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    Channel ch(&loop, nTimeFd);
    ch.SetReadCallback(timeout);
    ch.EnableReading();

    struct itimerspec HowLong;
    HowLong.it_value.tv_sec = 5;
    timerfd_settime(nTimeFd, 0, &HowLong, NULL);

    loop.Loop();

    return 0;
}
