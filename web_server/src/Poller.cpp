#include "common.h"
#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

Poller::Poller(EventLoop *pLoop):
    _m_pLoop(pLoop)
{
    //ctor
}

Poller::~Poller()
{
    //dtor
}

time_t Poller::Poll(int nTimeoutMs, ChannelList *pVecActiveChannel)
{
    int nNumEvents = poll(&*_m_vecPollFd.begin(), _m_vecPollFd.size(), nTimeoutMs);
    time_t nTimeNow;
    time(&nTimeNow);

    if(nNumEvents > 0)
    {
        FillActiveChannels(nNumEvents, pVecActiveChannel);
    }
    else if(nNumEvents < 0)
    {
        std::cerr << "Wrong With Poll" << std::endl;
    }

    return nTimeNow;
}

// find active channel
void Poller::FillActiveChannels(int nNumEvents, ChannelList* pVecActiveChannel) const
{
    for(PollFdList::const_iterator PollFdIte = _m_vecPollFd.begin(); PollFdIte != _m_vecPollFd.end() && nNumEvents > 0; ++PollFdIte)
    {
        if(PollFdIte->revents)
        {
            --nNumEvents;
            ChannelMap::const_iterator ChannelIte = _m_mapChannels.find(PollFdIte->fd);
            assert(ChannelIte != _m_mapChannels.end());
            Channel *pChannel = ChannelIte->second;
            assert(pChannel->fd() == PollFdIte->fd);
            pChannel->SetRevent(PollFdIte->revents);
            pVecActiveChannel->push_back(pChannel);
        }
    }
}

// Add and Update Channel
void Poller::UpdateChannel(Channel *pChannel)
{
    AssertInLoopThread();
    if(pChannel->Index() < 0)
    {
        // New Channel
        assert(_m_mapChannels.find(pChannel->fd()) == _m_mapChannels.end());

        struct pollfd NewPollfd;
        NewPollfd.fd = pChannel->fd();
        NewPollfd.events = static_cast<short>(pChannel->events());
        NewPollfd.revents = 0;

        _m_vecPollFd.push_back(NewPollfd);
        pChannel->SetIndex(static_cast<int>(_m_vecPollFd.size()) - 1);
        _m_mapChannels[NewPollfd.fd] = pChannel;
    }
    else
    {
        // Update exist Channel
        assert(_m_mapChannels.find(pChannel->fd()) != _m_mapChannels.end());
        assert(_m_mapChannels[pChannel->fd()] == pChannel);

        int nIndex = pChannel->Index();
        assert(0 <= nIndex && nIndex < static_cast<int>(_m_vecPollFd.size()));

        struct pollfd &CurPollFd = _m_vecPollFd[nIndex];
        assert(CurPollFd.fd == pChannel->fd() || CurPollFd.fd == -1);

        CurPollFd.events = static_cast<short>(pChannel->events());
        CurPollFd.revents = 0;
        if(pChannel->IsNoneEvent())
        {
            CurPollFd.fd = -1;
        }
    }

}










