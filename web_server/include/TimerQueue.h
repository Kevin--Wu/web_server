#ifndef TIMERQUEUE_H
#define TIMERQUEUE_H

#include "common.h"

class EventLoop;
class TimerId;

class TimerQueue
{
    public:
        TimerQueue(EventLoop *pLoop);
        virtual ~TimerQueue();

        TimerId AddTimer(const TimerCallback cb, time_t nWhen, double fInterval);
    protected:
    private:
};

#endif // TIMERQUEUE_H
