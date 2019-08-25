#include "Channel.h"
#include "EventLoop.h"
#include "common.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *Loop, int nFd):
    _m_pLoop(Loop),
    _m_nFd(nFd),
    _m_nEvents(0),
    _m_nRevents(0),
    _m_nIndex(-1)
{
    //ctor
}

Channel::~Channel()
{
    //dtor
}

void Channel::Update()
{
    _m_pLoop->UpdateChannel(this);
}

void Channel::HandleEvent()
{
    if (_m_nRevents & POLLNVAL)
    {
        std::cerr << "Handle Event POLLNVAL" << std::endl;
    }

    if (_m_nRevents & (POLLERR | POLLNVAL))
    {
        if(_m_errorCallback) _m_errorCallback();
    }
    if (_m_nRevents & (POLLIN | POLLPRI | POLLRDNORM))
    {
        if(_m_readCallback) _m_readCallback();
    }
    if (_m_nRevents & POLLOUT)
    {
        if(_m_writeCallback) _m_writeCallback();
    }
}









