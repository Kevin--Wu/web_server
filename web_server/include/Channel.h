#ifndef CHANNEL_H
#define CHANNEL_H

#include "common.h"
#include "EventLoop.h"

class Channel
{
    public:
        typedef void(*EventCallback)();

        Channel(EventLoop *Loop, int nFd);
        virtual ~Channel();

        void HandleEvent();
        void SetReadCallback(const EventCallback cb){ _m_readCallback = cb; }
        void SetWriteCallback(const EventCallback cb){ _m_writeCallback = cb; }
        void SetErrorCallback(const EventCallback cb){ _m_errorCallback = cb; }

    protected:
    private:
        EventCallback _m_readCallback;
        EventCallback _m_writeCallback;
        EventCallback _m_errorCallback;

};

#endif // CHANNEL_H
