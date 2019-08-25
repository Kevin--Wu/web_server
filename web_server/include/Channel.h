#ifndef CHANNEL_H
#define CHANNEL_H

#include "common.h"

class EventLoop;

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

        int fd() const { return _m_nFd; }
        int events() const { return _m_nEvents; }
        void SetRevent(int nEvents) { _m_nRevents = nEvents; }
        bool IsNoneEvent() const { return _m_nEvents == kNoneEvent; }

        void EnableReading() { _m_nEvents |= kReadEvent; Update(); }

        // For Poller
        int Index() { return _m_nIndex; }
        void SetIndex(int nID) { _m_nIndex = nID; }

        EventLoop* GetOwnerLoop() { return _m_pLoop; }

    protected:
    private:
        void Update();

        static const int kNoneEvent;
        static const int kReadEvent;
        static const int kWriteEvent;

        EventCallback _m_readCallback;
        EventCallback _m_writeCallback;
        EventCallback _m_errorCallback;

        EventLoop *_m_pLoop;
        const int _m_nFd;
        int _m_nEvents;
        int _m_nRevents;
        int _m_nIndex;

};

#endif // CHANNEL_H
