#include "EventLoop.h"
#include "common.h"


EventLoop* g_pLoopInThisThread = NULL;

EventLoop::EventLoop():
    _m_bLooping(false),
    _m_nThreadId(pthread_self())
{
    assert(g_pLoopInThisThread == NULL);
    g_pLoopInThisThread = this;
}

EventLoop::~EventLoop()
{
    assert(!_m_bLooping);
    g_pLoopInThisThread = NULL;
}

EventLoop* EventLoop::GetLoopInThisThread()
{
    return g_pLoopInThisThread;
}

void EventLoop::Loop()
{
    assert(!_m_bLooping);
    assert(InLoopThread());

    _m_bLooping = true;
    sleep(5);
    _m_bLooping = false;
}

bool EventLoop::InLoopThread() const
{
    return _m_nThreadId == pthread_self();
}








