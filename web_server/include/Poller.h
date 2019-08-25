#ifndef POLLER_H
#define POLLER_H

#include "common.h"

struct pollfd;
class Channel;
class EventLoop;

class Poller
{
    public:
        typedef std::vector<Channel*> ChannelList;

        Poller(EventLoop *pLoop);
        virtual ~Poller();

        time_t Poll(int nTimeoutMs, ChannelList *pActiveChannel);

        void UpdateChannel(Channel *pChannel);
        void AssertInLoopThread() { _m_pLoop->AssertInLoopThread(); }

    protected:
    private:
        void FillActiveChannels(int nNumEvents, ChannelList* pVecActiveChannel) const;

        typedef std::vector<struct pollfd> PollFdList;
        typedef std::map<int, Channel*> ChannelMap;

        EventLoop *_m_pLoop;
        PollFdList _m_vecPollFd;
        ChannelMap _m_mapChannels;
};

#endif // POLLER_H
