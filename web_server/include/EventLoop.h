#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "common.h"

class EventLoop
{
    public:
        EventLoop();
        virtual ~EventLoop();

        void Loop();
        bool InLoopThread() const;

        static EventLoop* GetLoopInThisThread();
    protected:
    private:
        const pthread_t _m_nThreadId;
        bool _m_bLooping;
};

#endif // EVENTLOOP_H
