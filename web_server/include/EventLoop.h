#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "common.h"

class Poller;
class Channel;

class EventLoop
{
    public:
        EventLoop();
        virtual ~EventLoop();

        void Loop();
        bool InLoopThread() const;
        void AssertInLoopThread()
        {
            if(!InLoopThread())
            {
                assert(false);
            }
        }
        void Quit();
        void UpdateChannel(Channel *pCh);

        static EventLoop* GetLoopInThisThread();
    protected:
    private:
        typedef std::vector<Channel*> ChannelList;

        bool _m_bLooping;
        bool _m_bQuit;
        Poller* _m_pPoller;
        ChannelList _m_vecActiveChannels;
        const pthread_t _m_nThreadId;

};

#endif // EVENTLOOP_H
