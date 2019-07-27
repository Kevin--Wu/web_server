#include <iostream>
using namespace std;

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ClientReactor.h"
#include "EventLoop.h"

void *Routine(void* arg)
{
    ClientReactor* pClReactor = (ClientReactor *)arg;



    while(true)
    {
        unsigned nOptVal;
        socklen_t nUnsignLen = sizeof(int);
        getsockopt(pClReactor->m_nClientFd, SOL_SOCKET, SO_SNDBUF, (char*)&nOptVal, &nUnsignLen);
        cout<<"Send len "<<nOptVal<<endl;
        getsockopt(pClReactor->m_nClientFd, SOL_SOCKET, SO_RCVBUF, (char*)&nOptVal, &nUnsignLen);
        cout<<"Recv len "<<nOptVal<<endl;

        int nMaxSendLen = 1024;
        char szSend[nMaxSendLen] = "hello internet";
        int nSendLen = send(pClReactor->m_nClientFd, szSend, nMaxSendLen, 0);
        cout<<nSendLen<<endl;
        sleep(3);
    }

    return NULL;
}

