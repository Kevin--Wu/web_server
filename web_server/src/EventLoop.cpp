#include "EventLoop.h"
#include "common.h"
#include "Poller.h"
#include "Channel.h"


EventLoop* g_pLoopInThisThread = NULL;

EventLoop::EventLoop():
    _m_bLooping(false),
    _m_nThreadId(pthread_self())
{
    assert(g_pLoopInThisThread == NULL);
    g_pLoopInThisThread = this;

    _m_pPoller = new Poller(this);
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
    _m_bQuit = false;

    while (!_m_bQuit)
    {
        _m_vecActiveChannels.clear();
        _m_pPoller->Poll(1000, &_m_vecActiveChannels);
        for(ChannelList::iterator ChannelIte = _m_vecActiveChannels.begin();
            ChannelIte != _m_vecActiveChannels.end(); ++ChannelIte)
        {
            (*ChannelIte)->HandleEvent();
        }
    }

    _m_bLooping = false;
}

bool EventLoop::InLoopThread() const
{
    return _m_nThreadId == pthread_self();
}

void EventLoop::Quit()
{
    _m_bQuit = true;
}

void EventLoop::UpdateChannel(Channel *pCh)
{
    assert(pCh->GetOwnerLoop() == this);
    AssertInLoopThread();
    _m_pPoller->UpdateChannel(pCh);
}








